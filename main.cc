#include <iostream>
#include "driver.hpp"

int main(int argc, char* argv[]) try
{
    yy::driver drv{};

    for (int i = 1; i < argc; ++i)
        if      (argv[i] == std::string("-p")) drv.trace_parsing = true;
        else if (argv[i] == std::string("-s")) drv.trace_scanning = true;
        else                                   drv.parse(argv[i]);

  return 0;
}
catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
}