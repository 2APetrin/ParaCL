#pragma once

#include "numgrammar.tab.hh"
#include "location.hh"
#include "tree.hpp"
#include <FlexLexer.h>


namespace yy {

class NumDriver {

public:
  FlexLexer *plex_;

  yy::location location;

  para_tree::ast_tree tree;
  para_tree::detail::scope* curr_scope_ = nullptr;

  NumDriver(FlexLexer *plex) : plex_(plex), 
                               curr_scope_(static_cast<para_tree::detail::scope*>(tree.make_scope())) {}

  // parser::symbol_type yylex() {
  //   parser::symbol_type tt = static_cast<parser::symbol_type>(plex_->yylex(), location);

  //   // if (tt == yy::parser::token_type::NUMBER)
  //   //   yylval->as<para_tree::detail::i_node*>() = tree.make_number(std::atoi(plex_->YYText()));
    
  //   // else if (tt == yy::parser::token_type::ID)
  //   //   yylval->as<para_tree::detail::i_node*>() = tree.make_identifier(plex_->YYText(), curr_scope_);
      
  //   return tt;
  // }

  bool parse() {
    location.initialize();

    parser parser(this);
    bool res = parser.parse();
    return !res;
  }
};

} // namespace yy

