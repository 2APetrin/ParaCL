%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.token.constructor
%define api.value.type variant
%param {yy::driver* drv}

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

    namespace yy { class driver; }
}


%code provides
{
    #include "driver.hpp"

    #define YY_DECL yy::parser::symbol_type yylex(yy::driver* drv)

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
%nonassoc EQ NEQ
%nonassoc BL BLE GR GRE
%left     ADD SUB
%left     MUL DIV MOD
%nonassoc UPLUS UMINUS
%right    NOT

//--------------terminal--------------
%token <int> NUMBER
%token <std::string> ID


//------------non terminal------------
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
%nterm <ptd::i_node*> primary_expr
//--------------------------------

%start program

%%

program: scope {
#ifdef DUMP
    drv->tree.graphviz_dump();
#endif
    drv->tree.execute_tree();
}
;

scope: op scope { }
     | %empty   { }
     ;

op: expr SCOLON   { $$ = $1;              drv->curr_scope_->add_child($$); }
  | while         { $$ = $1;              drv->curr_scope_->add_child($$); }
  | if            { $$ = $1;              drv->curr_scope_->add_child($$); }
  | lang_func     { $$ = $1;              drv->curr_scope_->add_child($$); }
  | scope_br      { $$ = $1;              drv->curr_scope_->add_child($$); }
  | SCOLON        { $$ = drv->make_nop(); drv->curr_scope_->add_child($$); }
  ;

scope_br: scope_br_start scope SRB { $$ = $1; drv->reset_scope(); } ;

scope_br_start: SLB { drv->new_scope(); $$ = drv->curr_scope_; } ;

expr: primary_expr
    | expr ADD expr { $$ = drv->make_d_op<ptop::ADD>($1, $3); }
    | expr SUB expr { $$ = drv->make_d_op<ptop::SUB>($1, $3); }
    | expr MUL expr { $$ = drv->make_d_op<ptop::MUL>($1, $3); }
    | expr DIV expr { $$ = drv->make_d_op<ptop::DIV>($1, $3); }
    | expr MOD expr { $$ = drv->make_d_op<ptop::MOD>($1, $3); }
    | expr GR  expr { $$ = drv->make_d_op<ptop::GR> ($1, $3); }
    | expr GRE expr { $$ = drv->make_d_op<ptop::GRE>($1, $3); }
    | expr BL  expr { $$ = drv->make_d_op<ptop::BL> ($1, $3); }
    | expr BLE expr { $$ = drv->make_d_op<ptop::BLE>($1, $3); }
    | expr EQ  expr { $$ = drv->make_d_op<ptop::EQ> ($1, $3); }
    | expr NEQ expr { $$ = drv->make_d_op<ptop::NEQ>($1, $3); }
    | expr AND expr { $$ = drv->make_d_op<ptop::AND>($1, $3); }
    | expr OR  expr { $$ = drv->make_d_op<ptop::OR> ($1, $3); }
    | NOT expr      { $$ = drv->make_s_op<ptop::NOT>($2);     }
    | SUB expr %prec UMINUS { $$ = drv->make_s_op<ptop::UNARY_MINUS>($2); }
    | ADD expr %prec UPLUS  { $$ = $2; }
    | ID ASSIG expr {
        ptd::i_node* tmp = nullptr;
        ptd::scope* id_scope = drv->curr_scope_->is_visible($1);

        if (!id_scope) {
            tmp = drv->make_identifier($1, drv->curr_scope_);
            drv->curr_scope_->push_id($1);
        }
        else tmp = drv->make_identifier($1, id_scope);

        $$ = drv->make_d_op<ptop::ASSIG>(tmp, $3);
    }
    ;

primary_expr: KLB expr KRB { $$ = $2; }
 | ID {
    ptd::scope* id_scope = drv->curr_scope_->is_visible($1);

    if (!id_scope) {
        std::cerr << "This id is not visible in this scope: " << $1 << " " << @1.begin << ":" << @1.end << std::endl;
        $$ = drv->make_identifier("UNDEFIND");
        drv->set_not_ok();
    }
    else $$ = drv->make_identifier($1, id_scope);
 }
 | NUMBER   { $$ = drv->make_number($1); }
 | SCAN     { $$ = drv->make_scan();     }
 ;

if: if_start op %prec THEN {
        $$ = drv->make_d_op<ptop::IF>($1, drv->curr_scope_);
        drv->reset_scope();
}
  | if_start op else %prec ELSE {
        $$ = drv->make_t_op<ptop::IF_ELSE>($1, $3.first, $3.second);
        drv->reset_scope();
}
  ;

else: else_start op { $$ = std::make_pair($1, drv->curr_scope_); } ;

if_start: IF KLB expr KRB { drv->new_scope(); $$ = $3; } ;

else_start: ELSE {
    $$ = drv->curr_scope_;
    drv->reset_scope(); drv->new_scope();
} ;

while: while_start op {
    $$ = drv->make_d_op<ptop::WHILE>($1, drv->curr_scope_);
    drv->reset_scope();
}
;

while_start: WHILE KLB expr KRB { drv->new_scope(); $$ = $3; } ;

lang_func: PRINT expr SCOLON { $$ = drv->make_s_op<ptop::PRINT>($2); } ;

%%

namespace yy {
    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}
