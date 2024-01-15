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

%union {
    char[32] id;
    int  number;
}

%token <number> NUMBER
%token <id> ID



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

program: comp
;

comp: op SCOLON comp
    | %empty
;

op: assig
  | while
  | if
  | func
  | SLB comp SRB
;

assig: ID EQ expr
     | ID EQ SCAN
;

expr: L GR  L
    | L GRE L
    | L BL  L
    | L BLE L
    | L EQ  L
    | L
;

L: T ADD T
 | T SUB T
 | T
;

T: P MUL P
 | P DIV P
 | P
;

P: KLB expr KRB
 | NUMBER
 | ID
;

if: IF KLB expr KRB op
;

while: WHILE KLB expr KRB op
;

func: FUNC KLB expr KRB
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
