#pragma once

#include "op_type.hpp"
#include "../symtab/symtab.hpp"
#include <iostream>
#include <fstream>
#include <vector>

namespace para_tree {


//--------------------------------DETAIL--------------------------------
namespace detail {

//----------------------------------------------------------------------
struct i_node {
    virtual void graphviz_dump(std::ofstream&) const = 0;
    virtual void dump() const = 0;
    virtual     ~i_node() = default;
};

//----------------------------------------------------------------------
struct i_executable : public virtual i_node {
    virtual void execute() const = 0;
};

//----------------------------------------------------------------------
struct i_calculatable : public virtual i_node {
    virtual int calc() const = 0;
};

//----------------------------------------------------------------------
class number final : public i_calculatable {
    int val_;

public:
    number(int val) : i_node(), i_calculatable(), val_(val) {}

    int calc() const override { return val_; }

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val=" << val_ << std::endl << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {val=" << val_ << "}}\", style = \"filled\", fillcolor = \"#FCE883\"];\n";
    }
};

//----------------------------------------------------------------------
class scope final : public i_executable {
    std::vector<const i_executable*> children_;

    para_symtab::symtab symtab_;
    scope* parent_scope_;

public:
    scope(scope* scope = nullptr) : i_node(), i_executable(), parent_scope_(scope) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "{\n";

        for (auto && i : children_) {
            std::cout << i << std::endl;
            i->dump();
        }

        std::cout << "}\n\n";
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {scope}}\", style = \"filled\", fillcolor = \"#9ACEEB\"];\n";

        for (auto && i : children_) {
            std::cout << "label1\n";
            i->graphviz_dump(out);
            out << "    node_" << this << "->node_" << i << " [color = \"#293133\"];\n";
        }
    }

    void add_child(const i_executable* chld) { std::cout << chld << std::endl; children_.push_back(chld); }

    void execute() const override {
        std::cout << "scope execution\n";
        for (auto && i : children_) { i->execute(); }
    }

    void dump_cont() {
        for (auto && i : children_) { std::cout << i << std::endl; }
    }

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

    void set_value(std::string &name, int value)  { symtab_.set_value(name, value); }
    int  get_value(const std::string &name) const { return symtab_.get_value(name); }
};

//----------------------------------------------------------------------
class identifier final : public i_calculatable {
    std::string name_;
    scope*      scope_;

public:
    identifier(std::string str, scope* scp = nullptr) : name_(str), scope_(scp) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var_name=" << name_ << std::endl << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {name=" << name_ << "}}\", style = \"filled\", fillcolor = \"#CDA4DE\"];\n";
    }

    //----------------------scope and symtab part----------------------
    int calc() const override { return scope_->get_value(name_); }
    void set_value(int value) { scope_->set_value(name_, value); }
};

//----------------------------------------------------------------------
struct two_child : public virtual i_node {
protected:
    i_node *l_, *r_;
    op_type type_;

public:
    two_child(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : l_(l), r_(r), type_(type) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "left =" << l_ << std::endl;
        std::cout << "right=" << r_ << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        auto ptr = dynamic_cast<detail::i_node*>(const_cast<two_child*>(this));
        out << "    node_" << ptr << "[shape = Mrecord, label = \"{{" << ptr << "} | {op_type=" << static_cast<int>(type_) << "}}\", style = \"filled\", fillcolor = \"#C5E384\"];\n";

        l_->graphviz_dump(out);
        r_->graphviz_dump(out);
        out << "    node_" << ptr << "->node_" << l_ << " [color = \"#293133\"];\n";
        out << "    node_" << ptr << "->node_" << r_ << " [color = \"#293133\"];\n";
    }

    void setl(i_node *newl) { l_ = newl; }
    void setr(i_node *newr) { r_ = newr; }
};

struct single_child : public virtual i_node {
    i_node *child_;
    op_type type_;

public:
    single_child(i_node *child = nullptr, op_type type = op_type::ERROR) : child_(child), type_(type) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "one child =" << child_ << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        auto ptr = dynamic_cast<detail::i_node*>(const_cast<single_child*>(this));
        out << "    node_" << ptr << "[shape = Mrecord, label = \"{{" << ptr << "} | {op_type=" << static_cast<int>(type_) << "}}\", style = \"filled\", fillcolor = \"#C5E384\"];\n";

        child_->graphviz_dump(out);
        out << "    node_" << ptr << "->node_" << child_ << " [color = \"#293133\"];\n";
    }

    void set_child(i_node *newc) { child_ = newc; }
};

//----------------------------------------------------------------------
template<op_type type>
struct exec_d_op final : public i_executable, public two_child { };

template<>
struct exec_d_op<op_type::ASSIG> final : public i_executable, public two_child {
    exec_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_executable(), two_child(l, r, type) {}

    void execute() const override {
        auto rs = dynamic_cast<number*>(r_);
        dynamic_cast<identifier*>(l_)->set_value(rs->calc());
    }
};

template<>
struct exec_d_op<op_type::IF> final : public i_executable, public two_child {
    exec_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_executable(), two_child(l, r, type) {}
    void execute() const override { std::cout << "op if\n"; }
};

template<>
struct exec_d_op<op_type::WHILE> final : public i_executable, public two_child {
    exec_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_executable(), two_child(l, r, type) {}
    void execute() const override { std::cout << "op while\n"; }
};

//----------------------------------------------------------------------
template<op_type type>
struct exec_s_op final : public i_executable, public single_child { };

template<>
struct exec_s_op<op_type::SCAN> final : public i_executable, public single_child {
    exec_s_op(i_node *chld = nullptr, op_type type = op_type::ERROR) : i_node(), i_executable(), single_child(chld, type) {}

    void execute() const override {
        int val = -1;

        while (!(std::cin >> val))
            std::cout << "Only integer type in ParaCL\n";

        dynamic_cast<identifier*>(child_)->set_value(val);
    }
};

//----------------------------------------------------------------------
template<op_type type>
struct calc_d_op final : public i_calculatable, public two_child { };

template<>
struct calc_d_op<op_type::ADD> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::SUB> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::MUL> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::DIV> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::GR> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::GRE> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::BL> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::BLE> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

template<>
struct calc_d_op<op_type::EQ> final : public i_calculatable, public two_child {
    calc_d_op(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : i_node(), i_calculatable(), two_child(l, r, type) {}
    int calc() const override { std::cout << "op ass\n"; }
};

} /*namespace detail*/

} /*namespace para_tree*/
