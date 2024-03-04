#include <iostream>

#include "numdriver.hpp"

extern "C" int yywrap() { return 1; }

int main() try
{
  yy::NumDriver driver{};
  driver.parse();
}
catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
}
