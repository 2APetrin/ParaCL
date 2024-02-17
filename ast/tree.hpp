#pragma once

#include <iostream>
#include <vector>
#include <memory>

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

//--------------------------------------------------------
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

//--------------------------------------------------------
class identifier final : public i_node {
    std::string name_;

public:
    identifier(std::string str) : name_(str) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var_name=" << name_ << std::endl << std::endl;
    }

    void execute() const override { std::cout << "id\n"; }
};

//--------------------------------------------------------
class scope final : public i_node {
    std::vector<const i_node*> children_;

public:
    scope() = default;

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "{\n";

        for (auto i : children_) {
            i->dump();
        }

        std::cout << "}\n\n";
    }

    void add_child(const i_node* chld) { children_.push_back(chld); }

    void execute() const override { std::cout << "scope\n"; }
};

//--------------------------------------------------------
class two_arg : public i_node {
    i_node *l_, *r_;
public:
    two_arg(i_node *l = nullptr, i_node *r = nullptr) : l_(l), r_(r) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "left =" << l_    << std::endl;
        std::cout << "right=" << r_    << std::endl;
    }

    void setl(i_node *newl) { l_ = newl; }
    void setr(i_node *newr) { l_ = newr; }
};

//--------------------------------------------------------
template<op_type type>
class para_operator final : public two_arg { };

//--------------------------------------------------------
template<> class para_operator<op_type::ADD> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "op add\n"; }
};

template<> class para_operator<op_type::SUB> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "op sub\n"; }
};

template<> class para_operator<op_type::MUL> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "op mul\n"; }
};

template<> class para_operator<op_type::DIV> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "op div\n"; }
};

template<> class para_operator<op_type::GR> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::GRE> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "gre op\n"; }
};

template<> class para_operator<op_type::BL> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "bl op\n"; }
};

template<> class para_operator<op_type::BLE> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "ble op\n"; }
};

template<> class para_operator<op_type::EQ> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::SCAN> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "scan op\n"; }
};

template<> class para_operator<op_type::ASSIG> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "assig op\n"; }
};

template<> class para_operator<op_type::IF> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "if op\n"; }
};

template<> class para_operator<op_type::WHILE> final : public two_arg {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr) : two_arg(l, r) {}
    void execute() const override { std::cout << "while op\n"; }
};


//---------------------------rule of zero---------------------------
class node_manager {
protected:
    std::vector<std::unique_ptr<i_node*>> node_container_;

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

    template <op_type type>
    node_ptr make_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        std::cout << static_cast<int>(type);
        auto node = new detail::para_operator<type>{l, r};
        node_container_.push_back(std::make_unique<node_ptr>(static_cast<node_ptr>(node)));
        return node;
    }

    void dump_cont() const {
        std::cout << "CONTAINER DUMP\n";
        for (auto i = node_container_.begin(), e = node_container_.end(); i != e; ++i) std::cout << *i << "\n";
    }
};

} /*namespace para tree*/