#pragma once

#include "numgrammar.tab.hh"
#include "para_tree.hpp"
#include <FlexLexer.h>

namespace yy {

class NumDriver {
  FlexLexer *plex_;

public:
  para_tree::inode* root_ = nullptr;
  NumDriver(FlexLexer *plex) : plex_(plex) {}

  parser::token_type yylex(parser::semantic_type *yylval) {
    parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());

    switch (tt) {
        case yy::parser::token_type::NUMBER:
            yylval->as<para_tree::inode*>() = new para_tree::num{ std::atoi(plex_->YYText()) };
            break;

        case yy::parser::token_type::ID:
            yylval->as<para_tree::inode*>() = new para_tree::id{ plex_->YYText() };
            break;
    }

    return tt;
  }

  bool parse() {
    parser parser(this);
    bool res = parser.parse();
    return !res;
  }
};

} // namespace yy
