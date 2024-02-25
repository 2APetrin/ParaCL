#pragma once

#include "numgrammar.tab.hh"
#include "location.hh"
#include "tree.hpp"
#include <FlexLexer.h>


namespace yy {

class NumDriver {

public:
  yy::location location;

  para_tree::ast_tree tree;
  para_tree::detail::scope* curr_scope_ = nullptr;

  NumDriver() : curr_scope_(static_cast<para_tree::detail::scope*>(tree.make_scope())) {}

  bool parse() {
    location.initialize();

    parser parser(this);
    bool res = parser.parse();
    return !res;
  }
};

} // namespace yy

