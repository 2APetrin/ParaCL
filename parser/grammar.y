%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.token.constructor
%define api.value.type variant
%param {yy::NumDriver* driver}

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

    namespace yy { class NumDriver; }

}


%code provides
{
    #include "numdriver.hpp"

    #define YY_DECL yy::parser::symbol_type yylex(yy::NumDriver* driver)

    YY_DECL;
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
%nterm <ptd::i_two_child*> assig
%nterm <ptd::i_two_child*> if
%nterm <ptd::i_two_child*> while
%nterm <ptd::i_two_child*> func
%nterm <ptd::i_two_child*> op
%nterm <ptd::i_two_child*> expr
%nterm <ptd::i_two_child*> L
%nterm <ptd::i_two_child*> Lsh
%nterm <ptd::i_two_child*> T
%nterm <ptd::i_two_child*> Tsh
%nterm <ptd::i_node*> P


%start program

%%

program: scope { /*driver->tree.execute_tree()*/ driver->tree.graphviz_dump(); }
;

scope: op scopesh { driver->curr_scope_->add_child($1); }
;

scopesh: op scopesh { driver->curr_scope_->add_child($1); }
      | %empty
;

op: assig         { $$ = $1; curr_scope_->add_child(static_cast<ptd::i_node*>($$)); }
  | while         { $$ = $1; curr_scope_->add_child(static_cast<ptd::i_node*>($$)); }
  | if            { $$ = $1; curr_scope_->add_child(static_cast<ptd::i_node*>($$)); }
  | func          { $$ = $1; curr_scope_->add_child(static_cast<ptd::i_node*>($$)); }
  | SLB scope SRB { 
        std::cout << "op { comp }" << std::endl; 
    }
;

assig: ID ASSIG expr SCOLON {
    //std::cout << "assig: id_name = " << $1 << std::endl;

    ptd::i_node* tmp = nullptr;
    ptd::scope* id_scope = driver->curr_scope_->is_visible($1);

    if (!id_scope) tmp = driver->tree.make_identifier($1, id_scope);
    else           tmp = driver->tree.make_identifier($1, driver->curr_scope_);

    $$ = driver->tree.make_ed_op<ptop::ASSIG>(tmp, static_cast<ptd::i_node>($3));
}
;

expr: L { $$ = $1; } 
    | L GR  L { driver->process_two_child_logic<ptop::GR> ($$, $1, $3); }
    | L GRE L { driver->process_two_child_logic<ptop::GRE>($$, $1, $3); }
    | L BL  L { driver->process_two_child_logic<ptop::BL> ($$, $1, $3); }
    | L BLE L { driver->process_two_child_logic<ptop::BLE>($$, $1, $3); }
    | L EQ  L { driver->process_two_child_logic<ptop::EQ> ($$, $1, $3); }
;

L: T Lsh {
    if ($2) { $2->setl($1); $$ = $2; }
    else                  { $$ = $1; }
}
;

Lsh: ADD T Lsh { driver->process_two_child_arith<ptop::ADD>($$, $2, $3); }
   | SUB T Lsh { driver->process_two_child_arith<ptop::SUB>($$, $2, $3); }
   | %empty
;

T: P Tsh {
    if ($2) { $2->setl($1); $$ = $2; }
    else                  { $$ = $1; }
}
;

Tsh: MUL P Tsh { driver->process_two_child_arith<ptop::MUL>($$, $2, $3); }
   | DIV P Tsh { driver->process_two_child_arith<ptop::DIV>($$, $2, $3); }
   | %empty
;

P: KLB expr KRB { $$ = $2; }
| ID {
    std::cout << "id: id_name = " << $1 << std::endl;

    if (!driver->curr_scope_->is_visible($1)) {
        std::cout << "This id is not visible in this scope: " << $1 << " " << @1.begin << ":" << @1.end << std::endl;
        $$ = driver->tree.make_identifier("UNDEFIND");
    }

    else 
        $$ = driver->tree.make_identifier($1, driver->curr_scope_);
}
 | NUMBER   { $$ = driver->tree.make_number($1); }
 | SCAN     { $$ = driver->tree.make_scan(); } 
;

if: IF KLB expr KRB op { $$ = make_d_op<ptop::IF>($3, $5); }
;

while: WHILE KLB expr KRB op { $$ = make_d_op<ptop::WHILE>($3, $5); }
;

func: FUNC KLB expr KRB SCOLON { $$ = make_s_op<ptop::PRINT>($3); }
; 

%%

namespace yy {
    /* parser::symbol_type yylex(NumDriver* driver) {
        return driver->yylex();
    } */

    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}
