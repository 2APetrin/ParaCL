%option c++

%{

using std::cout;
using std::endl;

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
ID      [a-z_]+

%%

{WS}              /* skip blanks and tabs */

"+"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
"-"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
"*"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
"/"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
"?"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
"="               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }

"("               { cout << "open  br <" << yytext[0] << ">" << endl; return 1; }
")"               { cout << "close br <" << yytext[0] << ">" << endl; return 1; }
"{"               { cout << "open br  <" << yytext[0] << ">" << endl; return 1; }
"}"               { cout << "close br <" << yytext[0] << ">" << endl; return 1; }

";"               { cout << "end op <"   << yytext[0] << ">" << endl; return 1; }

"<"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
">"               { cout << "operator <" << yytext[0] << ">" << endl; return 1; }
">="              { cout << "operator <" << yytext    << ">" << endl; return 1; }
"<="              { cout << "operator <" << yytext    << ">" << endl; return 1; }
"=="              { cout << "operator <" << yytext    << ">" << endl; return 1; }

"if"              { cout << "operator <" << yytext    << ">" << endl; return 1; }
"while"           { cout << "loop <"     << yytext    << ">" << endl; return 1; }
"print"           { cout << "function <" << yytext    << ">" << endl; return 1; }

{ID}              { cout << "variable <" << yytext    << ">" << endl; return 1; }

{DIGIT1}{DIGIT}*  { cout << "  number <" << yytext    << ">" << endl; return 1; }
.                 { cout << " UNKNOWN <" << yytext[0] << ">" << endl; return 1; }

%%