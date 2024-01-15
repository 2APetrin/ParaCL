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
%token <std::string> ID



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


%start program

%%

program: comp { std::cout << "chich1" << std::endl; }
;

comp: op SCOLON comp { std::cout << "chich2" << std::endl; }
    | %empty         { std::cout << "chich3" << std::endl; }
;

op: assig        { std::cout << "chich4" << std::endl; }
  | while        { std::cout << "chich5" << std::endl; }
  | if           { std::cout << "chich6" << std::endl; }
  | func         { std::cout << "chich7" << std::endl; }
  | SLB comp SRB { std::cout << "chich8" << std::endl; }
;

assig: ID EQ expr { std::cout << "chich9" << std::endl; }
     | ID EQ SCAN { std::cout << "chich10" << std::endl; }
;

expr: L GR  L { std::cout << "chich11" << std::endl; }
    | L GRE L { std::cout << "chich12" << std::endl; }
    | L BL  L { std::cout << "chich13" << std::endl; }
    | L BLE L { std::cout << "chich14" << std::endl; }
    | L EQ  L { std::cout << "chich15" << std::endl; }
    | L       { std::cout << "chich16" << std::endl; }
;

L: T ADD T { std::cout << "chich17" << std::endl; }
 | T SUB T { std::cout << "chich18" << std::endl; }
 | T       { std::cout << "chich19" << std::endl; }
;

T: P MUL P { std::cout << "chich20" << std::endl; }
 | P DIV P { std::cout << "chich21" << std::endl; }
 | P       { std::cout << "chich22" << std::endl; }
;

P: KLB expr KRB { std::cout << "chich23" << std::endl; }
 | NUMBER       { std::cout << "chich24" << std::endl; }
 | ID           { std::cout << "chich25" << std::endl; }
;

if: IF KLB expr KRB op { std::cout << "chich26" << std::endl; }
;

while: WHILE KLB expr KRB op { std::cout << "chich27" << std::endl; }
;

func: FUNC KLB expr KRB { std::cout << "chich28" << std::endl; }
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
