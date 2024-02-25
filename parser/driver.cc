#include <iostream>

#include "numdriver.hpp"

extern "C" int yywrap() { return 1; }

int main() {
  yy::NumDriver driver{};
  driver.parse();
}
