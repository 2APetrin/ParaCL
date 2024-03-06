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
    #include "tree.hpp"

    namespace ptd  = para_tree::detail;
    using     ptop = para_tree::op_type;

    namespace yy { class NumDriver; }
}


%code provides
{
    #include "numdriver.hpp"

    #define YY_DECL yy::parser::symbol_type yylex(yy::NumDriver* driver)

    YY_DECL;
}

%precedence ELSE "else"

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
    NEQ    "!="

    MOD    "%"
    NOT    "!"
    AND    "&&"
    OR     "||"

    IF     "if"
    WHILE  "while"
    PRINT  "print"

    ERR
;

//--------------terminal--------------
%token <int> NUMBER
%token <std::string> ID


//--------------non terminal--------------
%nterm <ptd::i_node*> scope
%nterm <ptd::i_node*> scope_br
%nterm <ptd::i_node*> scope_br_start

%nterm <ptd::i_node*> op
%nterm <ptd::i_node*> op_opened
%nterm <ptd::i_node*> op_closed
%nterm <ptd::i_node*> op_simple

/* %nterm <ptd::i_node*> if
%nterm <ptd::i_node*> if_start */

/* %nterm <ptd::i_two_child*> while
%nterm <ptd::i_node*>      while_start */

%nterm <ptd::i_one_child*> lang_func

//--------------expr--------------
%nterm <ptd::i_node*> logic
%nterm <ptd::i_node*> logic_rec
%nterm <ptd::i_node*> logic_expr

%nterm <ptd::i_node*> expr

%nterm <ptd::i_node*> T
%nterm <ptd::i_node*> T_rec

%nterm <ptd::i_node*> M
%nterm <ptd::i_node*> M_rec

%nterm <ptd::i_node*> Q
%nterm <ptd::i_node*> Q_rec

%nterm <ptd::i_node*> G
%nterm <ptd::i_node*> P
//--------------------------------

%start program

%%

program: scope { driver->tree.graphviz_dump(); /*driver->tree.execute_tree();*/ } ;

scope: op scope { }
     | %empty   { }
;

op: op_closed { }
  | op_opened { }
;

//if_start op %prec ELSE op { $$ = driver->make_t_op<ptop::IF_ELSE>($1, $2, $3); } // I've written make_t_op for if with else use it! Ne cringe li ya sdelal?
op_opened: IF KLB expr KRB op_opened                { std::cout << "cock-1\n"; }
         | IF KLB expr KRB op_closed                { std::cout << "cock0\n";  }
         | IF KLB expr KRB op_closed ELSE op_opened { std::cout << "cock1\n";  }
         | while_opened                             { }
         ;

op_closed: op_simple                                { }
         | IF KLB expr KRB op_closed ELSE op_closed { std::cout << "cock2\n"; }
         | while_closed                             { }
         ;

op_simple: expr SCOLON   { $$ = $1; driver->curr_scope_->add_child($$); }
         | lang_func     { $$ = $1; driver->curr_scope_->add_child($$); }
         | scope_br      { $$ = $1; driver->curr_scope_->add_child($$); }
         ;

while_opened: WHILE KLB expr KRB op_opened { } ; // rewrite using while_start

while_closed: WHILE KLB expr KRB op_closed { } ; // rewrite using while_start

lang_func: PRINT expr SCOLON { } ;

scope_br: scope_br_start scope SRB { $$ = $1; driver->reset_scope(); } ;

scope_br_start: SLB { driver->new_scope(); $$ = driver->curr_scope_; } ;

expr: M { }
    | ID ASSIG expr { // rewrite, vigladit huevo
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

// FUCK nado podumat' nad naming. M, Q, G, T huita
M: Q M_rec { } ;

M_rec: OR Q M_rec { }
     | %empty     { }
     ;

Q: logic_expr Q_rec { } ;

Q_rec: AND logic_expr Q_rec { }
     | %empty               { }
     ;

logic_expr : logic { $$ = $1; }
           | logic GR  logic { driver->process_two_child_logic<ptop::GR> ($$, $1, $3); }
           | logic GRE logic { driver->process_two_child_logic<ptop::GRE>($$, $1, $3); }
           | logic BL  logic { driver->process_two_child_logic<ptop::BL> ($$, $1, $3); }
           | logic BLE logic { driver->process_two_child_logic<ptop::BLE>($$, $1, $3); }
           | logic EQ  logic { driver->process_two_child_logic<ptop::EQ> ($$, $1, $3); }
           | logic NEQ logic { driver->process_two_child_logic<ptop::NEQ>($$, $1, $3); }
           ;

logic: T logic_rec {
    if ($2) { static_cast<ptd::i_two_child*>($2)->setl($1); $$ = $2; }
    else    { $$ = $1; }
}
;

logic_rec: ADD T logic_rec { driver->process_two_child_arith<ptop::ADD>($$, $2, $3); }
         | SUB T logic_rec { driver->process_two_child_arith<ptop::ADD>($$, driver->make_s_op<ptop::UNARY_MINUS>($2), $3); }
         | %empty          { }
         ;

T: G T_rec {
    if ($2) { static_cast<ptd::i_two_child*>($2)->setl($1); $$ = $2; }
    else    { $$ = $1; }
}
;

T_rec: MUL G T_rec { driver->process_two_child_arith<ptop::MUL>($$, $2, $3); }
     | DIV G T_rec { driver->process_two_child_arith<ptop::DIV>($$, $2, $3); }
     | %empty      { }
     ;

G: SUB P { $$ = driver->make_s_op<ptop::UNARY_MINUS>($2); };
 | ADD P { $$ = $2; }
 | NOT P { $$ = driver->make_s_op<ptop::NOT>($2); }
 | P     { $$ = $1; }
 ;

P: KLB expr KRB { $$ = $2; }
 | ID {
    ptd::scope* id_scope = driver->curr_scope_->is_visible($1);

    if (!id_scope) {
        std::cout << "This id is not visible in this scope: " << $1 << " " << @1.begin << ":" << @1.end << std::endl;
        $$ = driver->make_identifier("UNDEFIND");
        driver->set_not_ok();
    }
    else $$ = driver->make_identifier($1, id_scope);
 }
 | NUMBER   { $$ = driver->make_number($1); }
 | SCAN     { $$ = driver->make_scan(); }
 ;

%%

namespace yy {
    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}
