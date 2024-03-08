#include <iostream>

#include "driver.hpp"
#include "lexer.hh"

extern "C" int yywrap() { return 1; }

void yy::driver::parse_begin(const std::string& file)
{
    yyset_debug(trace_scanning);

    if (file.empty () || file == "-") yyin = stdin;

    else if (!(yyin = fopen (file.c_str (), "r"))) {
        std::cerr << "Cannot open " << file << std::endl;
        throw std::runtime_error("Bad file to parse");
    }
}

void yy::driver::parse_end() { fclose(yyin); }

bool yy::driver::parse(const std::string& file) {
    parse_begin(file);
    location.initialize(&file);

    yy::parser parser(this);
    parser.set_debug_level(trace_parsing);

    bool res = parser.parse();

    parse_end();

    return !res;
}
