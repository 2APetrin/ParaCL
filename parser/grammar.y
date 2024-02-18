%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::NumDriver* driver}


%code requires
{
    #include <iostream>
    #include "para_tree.hpp"
    #include <string>

    namespace yy { class NumDriver; } // forward decl of argument to parser
}


%code
{
    #include "numdriver.hpp"

    namespace yy {
        parser::token_type yylex(parser::semantic_type* yylval, NumDriver* driver);
    }
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
    FUNC

    ERR
;


// terminal tokens
%token <int> NUMBER
%token <para_tree::inode*> ID


// non terminal
%nterm <para_tree::inode*> scope
%nterm <para_tree::inode*> assig
%nterm <para_tree::inode*> op
%nterm <para_tree::inode*> expr
%nterm <para_tree::inode*> L
%nterm <para_tree::inode*> Lsh
%nterm <para_tree::inode*> T
%nterm <para_tree::inode*> Tsh
%nterm <para_tree::inode*> P



%start program

%%

program: scope { std::cout << driver->root_ << std::endl;
                 driver->root_->dump(); } // there is main scope created in driver :)
;

scope: op scopesh { driver->curr_scope_->add_child(static_cast<para_tree::inode*>($1)); }
;

scopesh: op scopesh { driver->curr_scope_->add_child(static_cast<para_tree::inode*>($1)); }
      | %empty
;

op: assig         { $$ = $1; }
  /* | while         { std::cout << "op while"    << std::endl; }   ***add scope here and below***
  | if            { std::cout << "op if"       << std::endl; }      
  | func          { std::cout << "op func"     << std::endl; }
  | SLB scope SRB { std::cout << "op { comp }" << std::endl; } */
;

assig: ID ASSIG expr SCOLON {
    // std::cout << "penis = " << driver->plex_->YYText() << std::endl;
    // para_tree::inode* tmp = static_cast<para_tree::inode*>(new para_tree::id{$1});
    $$ = static_cast<para_tree::inode*>(new para_tree::op{para_tree::op_type::ASSIG, $1, $3});
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
    if ($2) {
        auto tmp = static_cast<para_tree::op*>($2);
        tmp->setl($1);
        $$ = $2;
    }
    else {
        $$ = $1;
    }
}
;

Lsh: ADD T Lsh {
    if ($3) {
        auto tmp  = new para_tree::op{para_tree::op_type::ADD};
        auto tmp2 = static_cast<para_tree::op*>($3);
        tmp2->setl($2);
        tmp->setr(tmp2);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
    else {
        auto tmp = new para_tree::op{para_tree::op_type::ADD};
        tmp->setr($2);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
}
   | SUB T Lsh {
    if ($3) {
        auto tmp = new para_tree::op{para_tree::op_type::SUB};
        tmp->setr($2);
        tmp->setl($$);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
    else {
        auto tmp = new para_tree::op{para_tree::op_type::SUB};
        tmp->setr($2);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
}
   | %empty
;

T: P Tsh {
    if ($2) {
        auto tmp = static_cast<para_tree::op*>($2);
        tmp->setl($1);
        $$ = static_cast<para_tree::inode*>($2);
    }
    else {
        $$ = $1;
    }
}
;

Tsh: MUL P Tsh {
    if ($3) {
        auto tmp = new para_tree::op{para_tree::op_type::MUL};
        tmp->setr($2);
        tmp->setl($$);
        $$ = static_cast<para_tree::inode*>($3);
    }
    else {
        auto tmp = new para_tree::op{para_tree::op_type::MUL};
        tmp->setr($2);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
}
   | DIV P Tsh {
    if ($3) {
        auto tmp = new para_tree::op{para_tree::op_type::DIV};
        tmp->setr($2);
        tmp->setl($$);
        $$ = static_cast<para_tree::inode*>($3);
    }
    else {
        auto tmp = new para_tree::op{para_tree::op_type::DIV};
        tmp->setr($2);
        $$ = static_cast<para_tree::inode*>(tmp);
    }
}
   | %empty
;

P: /* KLB expr KRB { $$ = $2; }
 | */ ID           { $$ = static_cast<para_tree::inode*>($1); }
 | NUMBER          { $$ = static_cast<para_tree::inode*>(new para_tree::num{$1}); }
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
    parser::token_type yylex(parser::semantic_type* yylval, NumDriver* driver) {
        return driver->yylex(yylval);
    }

    void parser::error(const std::string&){}
}
