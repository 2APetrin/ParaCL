#pragma once

#include <fstream>
#include "symtab.hpp"

namespace para_tree {

//---------------------------------------------------------------------
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
    WHILE,

    ERROR
};


//----------------------------------DETAIL----------------------------------
namespace detail {

struct i_node {
    virtual void execute() const = 0;
    virtual void dump() const = 0;
    virtual void graphviz_dump(std::ofstream&) const = 0;
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

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {val=" << val_ << "}}\", style = \"filled\", fillcolor = \"#FCE883\"];\n";
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

    void graphviz_dump(std::ofstream& out) const override {
        std::cout << "label0\n";
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {scope}}\", style = \"filled\", fillcolor = \"#9ACEEB\"];\n";

        for (auto && i : children_) {
            std::cout << "label1\n";
            i->graphviz_dump(out);
            out << "    node_" << this << "->node_" << &*i << " [color = \"#293133\"];\n";
            //out << "    node_" << *i << "->node_" << this << " [color = \"#140F0B\", style = dotted];\n";
        }
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

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {name=" << name_ << "}}\", style = \"filled\", fillcolor = \"#CDA4DE\"];\n";
    }

    void execute() const override { std::cout << "id\n"; }

    //-------------------scope and symtab part-------------------------
    void set_value(int value) { scope_->set_value(name_, value); }
};

//---------------------------------------------------------------------
class op_base : public i_node {
    i_node *l_, *r_;
    op_type type_;
public:
    op_base(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : l_(l), r_(r), type_(type) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "left =" << l_ << std::endl;
        std::cout << "right=" << r_ << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {op_type=" << static_cast<int>(type_) << "}}\", style = \"filled\", fillcolor = \"#C5E384\"];\n";

        l_->graphviz_dump(out);
        r_->graphviz_dump(out);
        out << "    node_" << this << "->node_" << l_ << " [color = \"#293133\"];\n";
        out << "    node_" << this << "->node_" << r_ << " [color = \"#293133\"];\n";
    }

    void setl(i_node *newl) { l_ = newl; }
    void setr(i_node *newr) { r_ = newr; }
};


//---------------------------------------------------------------------
template<op_type type>
class para_operator final : public op_base { };


template<> class para_operator<op_type::ADD> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "op add\n"; }
};

template<> class para_operator<op_type::SUB> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "op sub\n"; }
};

template<> class para_operator<op_type::MUL> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "op mul\n"; }
};

template<> class para_operator<op_type::DIV> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "op div\n"; }
};

template<> class para_operator<op_type::GR> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::GRE> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "gre op\n"; }
};

template<> class para_operator<op_type::BL> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "bl op\n"; }
};

template<> class para_operator<op_type::BLE> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "ble op\n"; }
};

template<> class para_operator<op_type::EQ> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "gr op\n"; }
};

template<> class para_operator<op_type::SCAN> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "scan op\n"; }
};

template<> class para_operator<op_type::ASSIG> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "assig op\n"; }
};

template<> class para_operator<op_type::IF> final : public op_base {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
    void execute() const override { std::cout << "if op\n"; }
};

template<> class para_operator<op_type::WHILE> final : public op_base  {
public:
    para_operator(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : op_base(l, r, type) {}
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

} /*namespace para_tree*/