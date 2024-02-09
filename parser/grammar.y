%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::NumDriver* driver}

%code requires
{
  #include <iostream>
  #include <string>

  // forward decl of argument to parser
  namespace yy { class NumDriver; }
}

%code
{
  #include "numdriver.hpp"

  namespace yy {

    parser::token_type yylex(parser::semantic_type* yylval,
                            NumDriver* driver);
    }
}

%token
  ADD
  SUB
  MUL
  DIV
  SCAN
  ASSIG

  KLB
  KRB

  SLB
  SRB

  SCOLON

  GR
  GRE
  BL
  BLE
  EQ

  IF
  WHILE
  FUNC

  ERR
;

/* %union {
    char id[32];
    int  number;
} */

%token <int> NUMBER
%token <char*> ID



/* %nterm <int> NT_COMP
%nterm <int> NT_OP
%nterm <int> NT_ASSIG
%nterm <int> NT_WHILE
%nterm <int> NT_IF
%nterm <int> NT_FUNC
%nterm <int> NT_EXPR
%nterm <int> NT_LOGIC
%nterm <int> NT_T
%nterm <int> NT_P */
%nterm <int> scope
%nterm <int> op


%start program

%%

program: scope { std::cout << "AAOO " << $1 << std::endl; }
;

scope: op scopesh { std::cout << "scope" << std::endl; }
;

scopesh: op scopesh { std::cout << "scopesh" << $1 << std::endl; }
      | %empty
;

op: assig         { std::cout << "op assig"    << std::endl; }
  | while         { std::cout << "op while"    << std::endl; }
  | if            { std::cout << "op if"       << std::endl; }
  | func          { std::cout << "op func"     << std::endl; }
  | SLB scope SRB { std::cout << "op { comp }" << std::endl; }
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

if: IF KLB expr KRB op { std::cout << "if rule" << std::endl; }
;

while: WHILE KLB expr KRB op { std::cout << "while rule" << std::endl; }
;

func: FUNC KLB expr KRB SCOLON { std::cout << "func rule" << std::endl; }
;

%%  

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,
                         NumDriver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}
