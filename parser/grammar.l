%option c++

%{

#include "numgrammar.tab.hh"
#include "para_tree.hpp"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
ID      [a-z_]+

%%

{WS}              /* skip blanks and tabs */

"+"               {std::cout << yytext << "\n"; return new }
"-"               {std::cout << yytext << "\n"; return yy::parser::token_type::SUB;}
"*"               {std::cout << yytext << "\n"; return yy::parser::token_type::MUL;}
"/"               {std::cout << yytext << "\n"; return yy::parser::token_type::DIV;}
"?"               {std::cout << yytext << "\n"; return yy::parser::token_type::SCAN;}
"="               {std::cout << yytext << "\n"; return yy::parser::token_type::ASSIG;}

"("               {std::cout << yytext << "\n"; return yy::parser::token_type::KLB;}
")"               {std::cout << yytext << "\n"; return yy::parser::token_type::KRB;}
"{"               {std::cout << yytext << "\n"; return yy::parser::token_type::SLB;}
"}"               {std::cout << yytext << "\n"; return yy::parser::token_type::SRB;}

";"               {std::cout << yytext << "\n"; return yy::parser::token_type::SCOLON;}

">"               {std::cout << yytext << "\n"; return yy::parser::token_type::GR;}
">="              {std::cout << yytext << "\n"; return yy::parser::token_type::GRE;}
"<"               {std::cout << yytext << "\n"; return yy::parser::token_type::BL;}
"<="              {std::cout << yytext << "\n"; return yy::parser::token_type::BLE;}
"=="              {std::cout << yytext << "\n"; return yy::parser::token_type::EQ;}

"if"              {std::cout << yytext << "\n"; return yy::parser::token_type::IF;}
"while"           {std::cout << yytext << "\n"; return yy::parser::token_type::WHILE;}
"print"           {std::cout << yytext << "\n"; return yy::parser::token_type::FUNC;}

{ID}              {std::cout << yytext << "\n"; return yy::parser::token_type::ID;}

{DIGIT1}{DIGIT}*  {std::cout << yytext << "\n"; return yy::parser::token_type::NUMBER;}
.                 {std::cout << yytext << "\n"; return yy::parser::token_type::ERR;}

%%
