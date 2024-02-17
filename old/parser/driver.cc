#include <iostream>

#include "numdriver.hpp"

int yyFlexLexer::yywrap() { return 1; }

int main() {
  FlexLexer *lexer = new yyFlexLexer;
  yy::NumDriver driver(lexer);
  driver.parse();
  delete lexer;
}
