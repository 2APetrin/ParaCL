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

    NumDriver() : curr_scope_(static_cast<ptd::scope*>(tree.make_scope()) {
        tree.set_root(curr_scope);
    }

    template <ptop type>
    ptd::i_two_child* make_d_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        return tree.make_ed_op<type>(l, r);
    }

    template <ptop type>
    ptd::i_one_child* make_s_op(node_ptr chld = nullptr) {
        return tree.make_es_op<type>(chld);
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

    ptd::i_node* make_scan() { return tree.make_scan(); }

    template <ptop type>
    void process_two_child_arith(ptd::i_two_child* &ret, ptd::i_two_child* left,
                                 ptd::i_two_child* right = nullptr) {
        ret = make_d_op<type>();

        if (right) {
            right->setl(left);
            ret->setr(right);
        }
        else ret->setr(left);
    }

    template <ptop type>
    void process_two_child_logic(ptd::i_two_child* &ret, ptd::i_two_child* left,
                                 ptd::i_two_child* right = nullptr) {
        ret = make_d_op<type>();
        ret->setl(left);
        ret->setr(right);
    }

    bool parse() {
        location.initialize();

        parser parser(this);
        bool res = parser.parse();
        return !res;
    }
};

} // namespace yy

