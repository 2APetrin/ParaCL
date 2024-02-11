%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::NumDriver* driver}


%code requires
{
    #include <iostream>
    #include "para_tree.hpp"
//    #include <string>

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
%token <std::string> ID


// non terminal
%nterm <para_tree::scope*> scope
%nterm <para_tree::op*> assig


%start program

%%

program: scope { driver->root_ = new para_tree::scope{}; }
;

scope: op scopesh { $$.add_child($1); }
;

scopesh: op scopesh { std::cout << "scopesh" << std::endl; }
      | %empty
;

op: assig         { std::cout << "op assig"    << std::endl; }
  /* | while         { std::cout << "op while"    << std::endl; }
  | if            { std::cout << "op if"       << std::endl; }
  | func          { std::cout << "op func"     << std::endl; }
  | SLB scope SRB { std::cout << "op { comp }" << std::endl; } */
;

assig: ID ASSIG expr SCOLON { std::cout << "assig rule" << std::endl; }
;

expr: L GR  L { std::cout << "L > L"    << std::endl; }
    | L GRE L { std::cout << "L >= L"   << std::endl; }
    | L BL  L { std::cout << "L < L"    << std::endl; }
    | L BLE L { std::cout << "L <= L"   << std::endl; }
    | L EQ  L { std::cout << "L == L"   << std::endl; }
    | L       { std::cout << "L single" << std::endl; }
;

L: T Lsh       { std::cout << "L rule" << std::endl; }
;

Lsh: ADD T Lsh { std::cout << "Lsh + T Lsh" << std::endl; }
   | SUB T Lsh { std::cout << "Lsh - T Lsh" << std::endl; }
   | %empty
;

T: P Tsh       { std::cout << "T rule" << std::endl; }
;

Tsh: MUL P Tsh { std::cout << "Tsh * P Tsh" << std::endl; }
   | DIV P Tsh { std::cout << "Tsh / P Tsh" << std::endl; }
   | %empty
;

P: KLB expr KRB { std::cout << "( expr )" << std::endl; }
 | ID           { std::cout << "P id" << std::endl; }
 | NUMBER       { std::cout << "P number" << std::endl; }
 | SCAN         { std::cout << "P scan"    << std::endl; }
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
