#pragma once

#include "numgrammar.tab.hh"
#include "para_tree.hpp"
#include <FlexLexer.h>

namespace yy {

class NumDriver {

public:
  FlexLexer *plex_;
  para_tree::scope* root_ = nullptr;
  para_tree::scope* curr_scope_ = nullptr;

  NumDriver(FlexLexer *plex) : plex_(plex) {}

  parser::token_type yylex(parser::semantic_type *yylval) {
    parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());

    switch (tt) {
        case yy::parser::token_type::NUMBER:
            yylval->as<int>() = std::atoi(plex_->YYText());
            break;

        case yy::parser::token_type::ID:
            yylval->as<std::string>() = plex_->YYText();
            break;

        case yy::parser::token_type::ADD:
            yylval->as<para_tree::inode*>() = new para_tree::op{para_tree::op_type::ADD};
            break;

        case yy::parser::token_type::ASSIG:
            yylval->as<para_tree::inode*>() = new para_tree::op{para_tree::op_type::ASSIG};
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
