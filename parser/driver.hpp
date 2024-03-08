#pragma once

#include "grammar.tab.hh"
#include "location.hh"
#include "tree.hpp"


namespace yy {

class driver {
    using node_ptr = para_tree::detail::i_node*;

public:
    yy::location location;

    // Whether to generate parser and scanner debug traces.
    bool trace_parsing  = false;
    bool trace_scanning = false;

    para_tree::ast_tree tree;
    ptd::scope* curr_scope_;

    driver() : curr_scope_(static_cast<ptd::scope*>(tree.make_scope())) {
        tree.set_root(curr_scope_);
    }

    template <ptop type>
    ptd::i_three_child* make_t_op(node_ptr fst = nullptr, node_ptr snd = nullptr, node_ptr trd = nullptr) {
        return tree.make_t_op<type>(fst, snd, trd);
    }

    template <ptop type>
    ptd::i_two_child* make_d_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        return tree.make_d_op<type>(l, r);
    }

    template <ptop type>
    ptd::i_one_child* make_s_op(node_ptr chld = nullptr) {
        return tree.make_s_op<type>(chld);
    }

    ptd::i_node* make_number(int val) {
        return tree.make_number(val);
    }

    ptd::i_node* make_identifier(std::string str, ptd::scope* scp = nullptr) {
        return tree.make_identifier(str, scp);
    }

    ptd::i_node* make_nop() {
        return tree.make_nop();
    }

    void new_scope() { 
        curr_scope_ = static_cast<ptd::scope*>(tree.make_scope(curr_scope_)); 
    }

    void reset_scope() {
        curr_scope_ = curr_scope_->get_parent();
    }

    ptd::i_node* make_scan() { return tree.make_scan(); }

    void set_not_ok() { tree.is_ok = false; }

    void parse_begin(const std::string& file);

    void parse_end();

    bool parse(const std::string& file);
};

} // namespace yy

