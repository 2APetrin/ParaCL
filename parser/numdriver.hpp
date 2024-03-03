#pragma once

#include "numgrammar.tab.hh"
#include "location.hh"
#include "tree.hpp"
#include <FlexLexer.h>


namespace yy {

class NumDriver {
    using node_ptr = para_tree::detail::i_node*;

public:
    yy::location location;

    para_tree::ast_tree tree;
    para_tree::detail::scope* curr_scope_ = nullptr;

    NumDriver() : curr_scope_(static_cast<ptd::scope*>(tree.make_scope()) {}

    template <ptop type>
    ptd::i_two_child* make_ed_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        return tree.make_ed_op(l, r);
    }

    template <ptop type>
    ptd::i_one_child* make_es_op(node_ptr chld = nullptr) {
        return tree.make_es_op(chld);
    }

    ptd::i_node* make_number(int val) {
        return tree.make_number(val);
    }

    ptd::i_node* make_identifier(std::string str, ptd::scope* scp = nullptr) {
        return tree.make_identifier(str, scp);
    }

    ptd::i_node* make_scope(ptd::scope* parent_scope = nullptr) {
        return tree.make_scope(parent_scope);   
    }

    bool parse() {
        location.initialize();

        parser parser(this);
        bool res = parser.parse();
        return !res;
    }
};

} // namespace yy

