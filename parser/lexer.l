
%option nounput noinput batch debug 

%{
    #include "grammar.tab.hh"
%}

WS      [ \t\v\r]+
NS      [\n]+
DIGIT   [0-9]
DIGIT1  [1-9]
ID_B    [A-Za-z_$]
ID_E    [A-Za-z_$0-9]

%{
    #define yyterminate() yy::parser::make_YYEOF(loc);
    #define YY_USER_ACTION loc.columns(yyleng);
%}
%%
%{
    yy::location& loc = drv->location;
    loc.step();
%}


{WS}              { loc.step(); }
{NS}              { loc.lines(yyleng); loc.step(); }

"+"               { return yy::parser::make_ADD(loc); }
"-"               { return yy::parser::make_SUB(loc); }
"*"               { return yy::parser::make_MUL(loc); }
"/"               { return yy::parser::make_DIV(loc); }
"?"               { return yy::parser::make_SCAN(loc);  }
"="               { return yy::parser::make_ASSIG(loc); }

"("               { return yy::parser::make_KLB(loc); }
")"               { return yy::parser::make_KRB(loc); }
"{"               { return yy::parser::make_SLB(loc); }
"}"               { return yy::parser::make_SRB(loc); }

";"               { return yy::parser::make_SCOLON(loc); }

">"               { return yy::parser::make_GR(loc);  }
">="              { return yy::parser::make_GRE(loc); }
"<"               { return yy::parser::make_BL(loc);  }
"<="              { return yy::parser::make_BLE(loc); }
"=="              { return yy::parser::make_EQ(loc);  }
"!="              { return yy::parser::make_NEQ(loc); }

"%"               { return yy::parser::make_MOD(loc); }
"!"               { return yy::parser::make_NOT(loc); }
"||"              { return yy::parser::make_OR(loc);  }
"&&"              { return yy::parser::make_AND(loc); }

"if"              { return yy::parser::make_IF(loc);    }
"else"            { return yy::parser::make_ELSE(loc);  }
"while"           { return yy::parser::make_WHILE(loc); }
"print"           { return yy::parser::make_PRINT(loc); }

"//".*            { }

{ID_B}{ID_E}*     { return yy::parser::make_ID(yytext, loc); }

0                 { return yy::parser::make_NUMBER(0, loc); }
{DIGIT1}{DIGIT}*  { return yy::parser::make_NUMBER(std::atoi(yytext), loc); }
.                 { throw  yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext)); }

<<EOF>>     { return yyterminate(); }

%%
