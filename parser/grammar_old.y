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
    #include <utility>

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

%precedence THEN
%precedence ELSE "else"

%right    ASSIG
%left     OR
%left     AND
%nonassoc EQ  NEQ
%nonassoc BL BLE GR GRE
%left     ADD SUB
%left     MUL DIV MOD
%nonassoc UPLUS UMINUS
%right    NOT

//--------------terminal--------------
%token <int> NUMBER
%token <std::string> ID


//--------------non terminal--------------
%nterm <ptd::i_node*> scope
%nterm <ptd::i_node*> scope_br
%nterm <ptd::i_node*> scope_br_start

%nterm <ptd::i_node*> if
%nterm <ptd::i_node*> if_start

%nterm <ptd::scope*> else_start
%nterm <std::pair<ptd::scope*, ptd::scope*>> else

%nterm <ptd::i_two_child*> while
%nterm <ptd::i_node*>      while_start

%nterm <ptd::i_one_child*> lang_func

//--------------expr--------------
%nterm <ptd::i_node*> op
%nterm <ptd::i_node*> expr
%nterm <ptd::i_node*> P //rename
//--------------------------------

%start program

%%

program: scope { driver->tree.graphviz_dump();
                 driver->tree.execute_tree(); } ;

scope: op scope { }
     | %empty   { }
     ;

op: expr SCOLON   { $$ = $1;                 driver->curr_scope_->add_child($$); }
  | while         { $$ = $1;                 driver->curr_scope_->add_child($$); } 
  | if            { $$ = $1;                 driver->curr_scope_->add_child($$); }
  | lang_func     { $$ = $1;                 driver->curr_scope_->add_child($$); }
  | scope_br      { $$ = $1;                 driver->curr_scope_->add_child($$); }
  | SCOLON        { $$ = driver->make_nop(); driver->curr_scope_->add_child($$); }
  ;

scope_br: scope_br_start scope SRB { $$ = $1; std::cout << "SCOPE_BR=" << $$ << std::endl; driver->reset_scope(); } ;

scope_br_start: SLB { driver->new_scope(); $$ = driver->curr_scope_; } ;

expr: P
    | expr ADD expr { $$ = driver->make_d_op<ptop::ADD>($1, $3); }
    | expr SUB expr { $$ = driver->make_d_op<ptop::SUB>($1, $3); std::cout << "penis\n"; }
    | expr MUL expr { $$ = driver->make_d_op<ptop::MUL>($1, $3); }
    | expr DIV expr { $$ = driver->make_d_op<ptop::DIV>($1, $3); }
    | expr MOD expr { $$ = driver->make_d_op<ptop::MOD>($1, $3); }
    | expr GR  expr { $$ = driver->make_d_op<ptop::GR> ($1, $3); }
    | expr GRE expr { $$ = driver->make_d_op<ptop::GRE>($1, $3); }
    | expr BL  expr { $$ = driver->make_d_op<ptop::BL> ($1, $3); }
    | expr BLE expr { $$ = driver->make_d_op<ptop::BLE>($1, $3); }
    | expr EQ  expr { $$ = driver->make_d_op<ptop::EQ> ($1, $3); }
    | expr NEQ expr { $$ = driver->make_d_op<ptop::NEQ>($1, $3); }
    | expr AND expr { $$ = driver->make_d_op<ptop::AND>($1, $3); }
    | expr OR  expr { $$ = driver->make_d_op<ptop::OR> ($1, $3); }
    | NOT expr      { $$ = driver->make_s_op<ptop::NOT>($2);     }
    | SUB expr %prec UMINUS { $$ = driver->make_s_op<ptop::UNARY_MINUS>($2); std::cout << "cock\n"; }
    | ADD expr %prec UPLUS  { $$ = $2; }
    | ID ASSIG expr {
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

if: if_start op %prec THEN {
        $$ = driver->make_d_op<ptop::IF>($1, driver->curr_scope_);
        driver->reset_scope();
        std::cout << "if variant\n";
}
  | if_start op else %prec ELSE {
        $$ = driver->make_t_op<ptop::IF_ELSE>($1, $3.first, $3.second);
        driver->reset_scope();
        std::cout << "else variant\n";
}
;

else: else_start op {
    $$ = std::make_pair($1, driver->curr_scope_);
}
;

//if_else_start: if_start op %prec ELSE { $$ = std::make_pair($1, driver->curr_scope_); } ;

if_start: IF KLB expr KRB { driver->new_scope(); $$ = $3; } ;

else_start: ELSE {
    $$ = driver->curr_scope_;
    driver->reset_scope(); driver->new_scope();
} ;

while: while_start op {
    $$ = driver->make_d_op<ptop::WHILE>($1, driver->curr_scope_);
    driver->reset_scope();
}
;

while_start: WHILE KLB expr KRB { driver->new_scope(); $$ = $3; } ;

lang_func: PRINT expr SCOLON { $$ = driver->make_s_op<ptop::PRINT>($2); } ;

%%

namespace yy {
    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}




//if_start op %prec ELSE op { $$ = driver->make_t_op<ptop::IF_ELSE>($1, $2, $3); }