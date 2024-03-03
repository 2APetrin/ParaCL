%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.token.constructor
%define api.value.type variant
%param {yy::NumDriver* driver} //may be ref? I'll try later

%locations
%define parse.trace
%define parse.error detailed
%define parse.lac full

%code requires
{
    #include <iostream>
    #include <string>
    #include "tree.hpp"

    namespace ptd = para_tree::detail;
    using ptop = para_tree::op_type;

    namespace yy { class NumDriver; } // forward decl of argument to parser

}


%code provides
{
    #include "numdriver.hpp"

    #define YY_DECL yy::parser::symbol_type yylex(yy::NumDriver* driver)

    YY_DECL;
}

%code
{
    
}


%token
    ADD    "+"
    SUB    "-"
    MUL    "*"
    DIV    "/"
    SCAN   "?"
    ASSIG  "="

    KLB    "("
    KRB    ")"

    SLB    "{"
    SRB    "}"

    SCOLON ";"

    GR     ">"
    GRE    ">="
    BL     "<"
    BLE    "<="
    EQ     "=="

    IF     "if"
    WHILE  "while"
    FUNC   "print"

    ERR
;


// terminal tokens
%token <int> NUMBER
%token <std::string> ID


// non terminal
%nterm <ptd::i_node*> scope
%nterm <ptd::two_child*> assig
%nterm <ptd::two_child*> op
%nterm <ptd::two_child*> expr
%nterm <ptd::two_child*> L
%nterm <ptd::two_child*> Lsh
%nterm <ptd::two_child*> T
%nterm <ptd::two_child*> Tsh
%nterm <ptd::i_node*> P


%start program

%%

program: scope { /*driver->tree.execute_tree()*/ driver->curr_scope_->dump(); driver->tree.set_root(driver->curr_scope_); driver->tree.graphviz_dump(); }
;

scope: op scopesh { driver->curr_scope_->add_child($1); }
;

scopesh: op scopesh { driver->curr_scope_->add_child($1); }
      | %empty
;

op: assig         { $$ = $1; /*$$->dump();*/ }
  /* | while         { std::cout << "op while"    << std::endl; }
  | if            { std::cout << "op if"       << std::endl; }
  | func          { std::cout << "op func"     << std::endl; }
  | SLB scope SRB { std::cout << "op { comp }" << std::endl; } */
;

assig: ID ASSIG expr SCOLON {
    std::cout << "assig: id_name = " << $1 << std::endl;

    ptd::i_node* tmp = nullptr;
    ptd::scope* id_scope = driver->curr_scope_->is_visible($1);

    if (!id_scope) tmp = driver->tree.make_identifier($1, id_scope);
    else           tmp = driver->tree.make_identifier($1, driver->curr_scope_);

    $$ = driver->tree.make_ed_op<ptop::ASSIG>(tmp, static_cast<ptd::i_node>($3));
}
;

expr: L { $$ = $1; /*$$->dump();*/ } /* GR  L { std::cout << "L > L"    << std::endl; }
    | L GRE L { std::cout << "L >= L"   << std::endl; }
    | L BL  L { std::cout << "L < L"    << std::endl; }
    | L BLE L { std::cout << "L <= L"   << std::endl; }
    | L EQ  L { std::cout << "L == L"   << std::endl; }
    | L       { std::cout << "L single" << std::endl; } */
;

L: T Lsh {
    if ($2) { $2->setl($1); $$ = $2; }
    else                  { $$ = $1; }
}
;

Lsh: ADD T Lsh {
    ptd::two_child* tmp1 = driver->make_cd_op<ptop::ADD>();

    if ($3) {
        ptd::op_base* tmp2 = static_cast<ptd::op_base*>($3);
        tmp2->setl($2);
        tmp1->setr($3);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
    else {
        tmp1->setr($2);
        $$ = static_cast<ptd::i_node*>(tmp1); 
    }
}
   | SUB T Lsh {
    ptd::op_base* tmp1 = static_cast<ptd::op_base*>(driver->tree.make_op<ptop::SUB>());

    if ($3) {
        ptd::op_base* tmp2 = static_cast<ptd::op_base*>($3);
        tmp2->setl($2);
        tmp1->setr($3);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
    else {
        tmp1->setr($2);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
}
   | %empty
;

T: P Tsh {
    if ($2) { static_cast<ptd::op_base*>($2)->setl($1); $$ = $2; }
    else    { $$ = $1; }
}
;

Tsh: MUL P Tsh {
    ptd::op_base* tmp1 = static_cast<ptd::op_base*>(driver->tree.make_op<ptop::MUL>());

    if ($3) {
        ptd::op_base* tmp2 = static_cast<ptd::op_base*>($3);
        tmp2->setl($2);
        tmp1->setr($3);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
    else {
        tmp1->setr($2);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
}
   | DIV P Tsh {
    ptd::op_base* tmp1 = static_cast<ptd::op_base*>(driver->tree.make_op<ptop::DIV>());

    if ($3) {
        ptd::op_base* tmp2 = static_cast<ptd::op_base*>($3);
        tmp2->setl($2);
        tmp1->setr($3);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
    else {
        tmp1->setr($2);
        $$ = static_cast<ptd::i_node*>(tmp1);
    }
}
   | %empty
;

P: /* KLB expr KRB { $$ = $2; }| */ 
    ID

    {
        std::cout << "id: id_name = " << $1 << std::endl;


        if (!driver->curr_scope_->is_visible($1)) {
            std::cout << "This id is not visible in this scope: " << $1 << " " << @1.begin << ":" << @1.end << std::endl;
            $$ = driver->tree.make_identifier("UNDEFIND");
        }

        else {
            $$ = driver->tree.make_identifier($1, driver->curr_scope_);
        }
    }
 | NUMBER          { $$ = static_cast<ptd::i_node*>(driver->tree.make_number($1)); }
 /* | SCAN         { $$ = $1; } */
;

/* if: IF KLB expr KRB op { std::cout << "if rule" << std::endl; }
;

while: WHILE KLB expr KRB op { std::cout << "while rule" << std::endl; }
;

func: FUNC KLB expr KRB SCOLON { std::cout << "func rule" << std::endl; }
; */

%%

namespace yy {
    /* parser::symbol_type yylex(NumDriver* driver) {
        return driver->yylex();
    } */

    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}
