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
    PRINT  "print"

    ERR
;


// terminal tokens
%token <int> NUMBER
%token <std::string> ID


// non terminal
%nterm <ptd::i_node*> scope
%nterm <ptd::i_node*> scope_br
%nterm <ptd::i_node*> scope_br_start

%nterm <ptd::i_two_child*> if
%nterm <ptd::i_node*>      if_start

%nterm <ptd::i_two_child*> while
%nterm <ptd::i_node*>      while_start

//%nterm <ptd::i_two_child*> assig
%nterm <ptd::i_one_child*> lang_func

%nterm <ptd::i_node*> op
%nterm <ptd::i_node*> expr
%nterm <ptd::i_node*> L
%nterm <ptd::i_node*> Lsh
%nterm <ptd::i_node*> T
%nterm <ptd::i_node*> Tsh
%nterm <ptd::i_node*> P
%nterm <ptd::i_node*> G


%start program

%%

program: scope { driver->tree.graphviz_dump(); driver->tree.execute_tree(); }
;

scope: op scopesh { }
;

scopesh: op scopesh { }
      | %empty
;

op: expr SCOLON   { $$ = $1; driver->curr_scope_->add_child($$); }
  | while         { $$ = $1; driver->reset_scope(); driver->curr_scope_->add_child($$); } 
  | if            { $$ = $1; driver->reset_scope(); driver->curr_scope_->add_child($$); }
  | lang_func     { $$ = $1; driver->curr_scope_->add_child($$); }
  | scope_br      { $$ = $1; driver->curr_scope_->add_child($$); }
;

scope_br: scope_br_start scope close_br { $$ = $1; std::cout << "SCOPE_BR=" << $$ << std::endl; }
;
scope_br_start: SLB { driver->new_scope(); $$ = driver->curr_scope_; }
;
close_br: SRB { driver->reset_scope(); }
;

expr: L { $$ = $1; }
    | L GR  L { driver->process_two_child_logic<ptop::GR> ($$, $1, $3); }
    | L GRE L { driver->process_two_child_logic<ptop::GRE>($$, $1, $3); }
    | L BL  L { driver->process_two_child_logic<ptop::BL> ($$, $1, $3); }
    | L BLE L { driver->process_two_child_logic<ptop::BLE>($$, $1, $3); }
    | L EQ  L { driver->process_two_child_logic<ptop::EQ> ($$, $1, $3); }
    | ID ASSIG expr {
        //std::cout << "assig: id_name = " << $1 << std::endl;

        ptd::i_node* tmp = nullptr;
        ptd::scope* id_scope = driver->curr_scope_->is_visible($1);

        if (!id_scope) {
            tmp = driver->make_identifier($1, driver->curr_scope_);
            driver->curr_scope_->push_id($1);
        }
        else tmp = driver->make_identifier($1, id_scope);

        $$ = driver->make_d_op<ptop::ASSIG>(tmp, $3);
}
;

L: T Lsh {
    if ($2) { static_cast<ptd::i_two_child*>($2)->setl($1); $$ = $2; }
    else    { $$ = $1; }
}
;

Lsh: ADD T Lsh { driver->process_two_child_arith<ptop::ADD>($$, $2, $3); }
   | SUB T Lsh { driver->process_two_child_arith<ptop::ADD>($$, driver->make_s_op<ptop::UNARY_MINUS>($2), $3); }
   | %empty
;

T: G Tsh {
    if ($2) { static_cast<ptd::i_two_child*>($2)->setl($1); $$ = $2; }
    else    { $$ = $1; }
}
;

Tsh: MUL G Tsh { driver->process_two_child_arith<ptop::MUL>($$, $2, $3); }
   | DIV G Tsh { driver->process_two_child_arith<ptop::DIV>($$, $2, $3); }
   | %empty
;

G:   SUB P { $$ = driver->make_s_op<ptop::UNARY_MINUS>($2); };
   | ADD P { $$ = $2; }
   | P       { $$ = $1; }
;

P: KLB expr KRB { $$ = $2; }
 | ID {
    ptd::scope* id_scope = driver->curr_scope_->is_visible($1);

    if (!id_scope) {
        std::cout << "This id is not visible in this scope: " << $1 << " " << @1.begin << ":" << @1.end << std::endl;
        $$ = driver->make_identifier("UNDEFIND");
        driver->set_not_ok();
    }

    else
        $$ = driver->make_identifier($1, id_scope);
}
 | NUMBER   { $$ = driver->make_number($1); }
 | SCAN     { $$ = driver->make_scan(); }
;

if: if_start op { $$ = driver->make_d_op<ptop::IF>($1, $2); std::cout << "IF=" << $$ << std::endl; }
;

if_start: IF KLB expr KRB { driver->new_scope(); $$ = $3; }
;

while: while_start op { $$ = driver->make_d_op<ptop::WHILE>($1, $2); }
;

while_start: WHILE KLB expr KRB { driver->new_scope(); $$ = $3; }
;

lang_func: PRINT expr SCOLON { $$ = driver->make_s_op<ptop::PRINT>($2); }
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
