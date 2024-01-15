%option c++

%{

#include "numgrammar.tab.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
ID      [a-z_]+

%%

{WS}              /* skip blanks and tabs */

"+"               return yy::parser::token_type::ADD;
"-"               return yy::parser::token_type::SUB;
"*"               return yy::parser::token_type::MUL;
"/"               return yy::parser::token_type::DIV;
"?"               return yy::parser::token_type::SCAN;
"="               return yy::parser::token_type::ASSIG;

"("               return yy::parser::token_type::KLB;
")"               return yy::parser::token_type::KRB;
"{"               return yy::parser::token_type::SLB;
"}"               return yy::parser::token_type::SRB;

";"               return yy::parser::token_type::SCOLON;

">"               return yy::parser::token_type::GR;
">="              return yy::parser::token_type::GRE;
"<"               return yy::parser::token_type::BL;
"<="              return yy::parser::token_type::BLE;
"=="              return yy::parser::token_type::EQ;

"if"              return yy::parser::token_type::IF;
"while"           return yy::parser::token_type::WHILE;
"print"           return yy::parser::token_type::FUNC;

{ID}              return yy::parser::token_type::ID;

{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
.                 return yy::parser::token_type::ERR;

%%
