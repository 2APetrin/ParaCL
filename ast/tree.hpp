#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "symtab.hpp"

namespace para_tree {

enum class op_type {
    ADD,
    SUB,
    MUL,
    DIV,

    GR,
    GRE,
    BL,
    BLE,
    EQ,

    SCAN,
    ASSIG,

    IF,
    WHILE
};

namespace detail {

struct i_node {
    virtual void execute() const = 0;
    virtual void dump() const = 0;
    virtual     ~i_node() = default;
};

//---------------------------------------------------------------------
class number final : public i_node {
    int val_;

public:
    number(int val) : val_(val) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val=" << val_ << std::endl << std::endl;
    }

    void execute() const override { std::cout << "num\n"; }
};


//---------------------------------------------------------------------
class scope final : public i_node {
    std::vector<const i_node*> children_;

    scope* parent_scope_;

    para_symtab::symtab symtab_;

public:
    scope(scope* scope = nullptr) : parent_scope_(scope) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "{\n";

        for (auto && i : children_) {
            i->dump();
        }

        std::cout << "}\n\n";
    }

    void add_child(const i_node* chld) { children_.push_back(chld); }

    void execute() const override { std::cout << "scope\n"; }

    //---------------------work with symtab-----------------------
    void push_id(std::string name, int value = 0) { symtab_.push_id(name, value); }

    scope* is_visible(std::string name) { 
        if (symtab_.is_visible(name)) return this;

        scope* curr = parent_scope_;
        
        while (curr != nullptr) {
            if (curr->symtab_.is_visible(name)) return curr;

            curr = curr->parent_scope_;
        }
        return nullptr;
    }

    void set_value(std::string name, int value) { symtab_.set_value(name, value); }
};

//---------------------------------------------------------------------
class identifier final : public i_node {
    std::string name_;

    scope* scope_;

public:
    identifier(std::string str, scope* scp = nullptr) : name_(str), scope_(scp) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var_name=" << name_ << std::endl << std::endl;
    }

    void execute() const override { std::cout << "id\n"; }

    //-------------------scope and symtab part-------------------------
    void set_value(int value) { scope_->set_value(name_, value); }
};

//---------------------------------------------------------------------
class op_base : public i_node {
    i_node *l_, *r_;
public:
    op_base(i_node *l = nullptr, i_node *r = nullptr) : l_(l), r_(r) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "left =" << l_    << std::endl;
        std::cout << "right=" << r_    << std::endl;
    }

    void setl(i_node *newl) { l_ = newl; }
    void setr(i_node *newr) { r_ = newr; }
};

//---------------------------------------------------------------------
template<op_type type>
class para_operator final : public op_base { };

//---------------------------------------------------------------------
template<> class para_operator<op_type::ADD> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "op add\n"; }
};

template<> class para_operator<op_type::SUB> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "op sub\n"; }
};

template<> class para_operator<op_type::MUL> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "op mul\n"; }
};

template<> class para_operator<op_type::DIV> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "op div\n"; }
};

template<> class para_operator<op_type::GR> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::GRE> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "gre op\n"; }
};

template<> class para_operator<op_type::BL> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "bl op\n"; }
};

template<> class para_operator<op_type::BLE> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "ble op\n"; }
};

template<> class para_operator<op_type::EQ> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::SCAN> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "scan op\n"; }
};

template<> class para_operator<op_type::ASSIG> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "assig op\n"; }
};

template<> class para_operator<op_type::IF> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "if op\n"; }
};

template<> class para_operator<op_type::WHILE> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : op_base(l, r) {}
    void execute() const override { std::cout << "while op\n"; }
};


//---------------------------rule of zero---------------------------
class node_manager {
protected:
    std::vector<std::unique_ptr<i_node>> node_container_;

protected:
    node_manager()  = default;
    ~node_manager() = default;

    node_manager            (const node_manager&) = delete;
    node_manager& operator= (const node_manager&) = delete;
    node_manager            (node_manager&&) = delete;
    node_manager& operator= (node_manager&&) = delete;
};

} /*namespace detail*/

class ast_tree final : private detail::node_manager {
    using node_ptr = detail::i_node*;

    using detail::node_manager::node_container_;
    node_ptr root_;

public:
    ast_tree() = default;

//---------------------------------------------------------------------
    template <op_type type>
    node_ptr make_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        detail::para_operator<type>* node = new detail::para_operator<type>{l, r};
        node_ptr base_node_ptr = static_cast<node_ptr>(node);

        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_number(int val) {
        detail::number* node = new detail::number{val};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_identifier(std::string str, detail::scope* scp = nullptr) {
        detail::identifier* node = new detail::identifier{str, scp};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_scope(detail::scope* parent_scope = nullptr) {
        detail::scope* node = new detail::scope{parent_scope};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
//    int execute_tree() const { }

//---------------------------------------------------------------------
    void set_root(node_ptr newroot) { root_ = newroot; }

    void dump_cont() const {
        std::cout << "CONTAINER DUMP\n";
        for (auto i = node_container_.begin(), e = node_container_.end(); i != e; ++i) {
            (*i)->execute();
            std::cout << " " << *i << "\n";
        }
    }
};

} /*namespace para tree*/