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
    virtual int  execute() const = 0;
    virtual void dump() const = 0;
    virtual     ~i_node() = default;
};

//----------------------------------------------------------------------
class number final : public i_node {
    int val_;
public:
    number(int val) : val_(val) {}

    int execute() const override { return val_; }

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val=" << val_ << std::endl << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {val=" << val_ << "}}\", style = \"filled\", fillcolor = \"#FCE883\"];\n";
    }
};

//----------------------------------------------------------------------
class scope final : public i_node {
    std::vector<const i_node*> children_;

    para_symtab::symtab symtab_;
    scope* parent_scope_;

public:
    scope(scope* scope = nullptr) : parent_scope_(scope) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "{\n";

        for (auto && i : children_) i->dump();

        std::cout << "}\n\n";
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {scope}}\", style = \"filled\", fillcolor = \"#9ACEEB\"];\n";

        for (auto && i : children_) {
            i->graphviz_dump(out);
            out << "    node_" << this << "->node_" << i << " [color = \"#293133\"];\n";
            std::cout << i << std::endl;
        }
    }

    scope* get_parent() { return parent_scope_; }

    void add_child(const i_node* chld) { children_.push_back(chld); }

    int execute() const override {
        for (auto && i : children_) i->execute();
        return 0;
    }

//--------------------------work with symtab----------------------------
    void push_id(std::string &name, int value = 0) { symtab_.push_id(name, value); }

    scope* is_visible(std::string &name) {
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
class identifier final : public i_node {
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
        out << "    node_" << this << "->node_" << scope_ << " [ style = \"dotted\", color = \"#293133\"];\n";
    }

    //----------------------scope and symtab part----------------------
    void set_value(int value)    { scope_->set_value(name_, value); }
    std::string get_name()       { return name_;                    }
    int execute() const override { return scope_->get_value(name_); }
};

//----------------------------------------------------------------------
struct i_one_child : public i_node {
protected:
    i_node *child_;
    op_type type_;

public:
    i_one_child(i_node *child = nullptr, op_type type = op_type::ERROR) : child_(child), type_(type) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "one child =" << child_ << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {op_type=" << static_cast<int>(type_) << "}}\", style = \"filled\", fillcolor = \"#C5E384\"];\n";

        child_->graphviz_dump(out);
        out << "    node_" << this << "->node_" << child_ << " [color = \"#293133\"];\n";
    }

    void set_child(i_node *newc) { child_ = newc; }
};

//----------------------------------------------------------------------
struct i_two_child : public i_node {
protected:
    i_node *l_, *r_;
    op_type type_;

public:
    i_two_child(i_node *l = nullptr, i_node *r = nullptr, op_type type = op_type::ERROR) : l_(l), r_(r), type_(type) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "left =" << l_ << std::endl;
        std::cout << "right=" << r_ << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {op_type=" << static_cast<int>(type_) << "}}\", style = \"filled\", fillcolor = \"#C5E384\"];\n";

        l_->graphviz_dump(out);
        r_->graphviz_dump(out);
        out << "    node_" << this << "->node_" << l_ << " [color = \"#FF2B2B\"];\n";
        out << "    node_" << this << "->node_" << r_ << " [color = \"#1164B4\"];\n";
    }

    void setl(i_node *newl) { l_ = newl; }
    void setr(i_node *newr) { r_ = newr; }
};

class scan final : public i_node {
    i_node* scan_id_;

public:
    scan() = default;

    int execute() const override {
        int val = 0;
        if (!(std::cin >> val))
            throw std::runtime_error{"Scan didn't scan integer type. Only integer type in ParaCL. Wait for ParaCL updates!!!\n"};

        return val;
    }

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "scan_id_name=" << static_cast<identifier*>(scan_id_)->get_name() << std::endl;
    }

    void graphviz_dump(std::ofstream& out) const override {
        out << "    node_" << this << "[shape = Mrecord, label = \"{{" << this << "} | {scan}}\", style = \"filled\", fillcolor = \"#CDA4DE\"];\n";

        scan_id_->graphviz_dump(out);
        out << "    node_" << this << "->node_" << scan_id_ << " [color = \"#293133\"];\n";
    }
};

//----------------------------------------------------------------------
template <op_type T>
struct one_child_op final : public i_one_child { };

template<>
struct one_child_op<op_type::PRINT> final : public i_one_child {
    one_child_op(i_node *child = nullptr) : i_one_child(child, op_type::PRINT) {}

    int execute() const override {
        std::cout << child_->execute() << std::endl;
        return 0;
    }
};

//----------------------------------------------------------------------
template <op_type T>
struct two_child_op final : public i_two_child { };

template<>
struct two_child_op<op_type::ADD> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::ADD) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return l + r;
    }
};

template<>
struct two_child_op<op_type::SUB> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::SUB) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return l - r;
    }
};

template<>
struct two_child_op<op_type::MUL> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::MUL) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return l * r;
    }
};

template<>
struct two_child_op<op_type::DIV> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::DIV) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        if (0 == r) throw std::runtime_error{"Division by zero.\nYou still can't divide by zero. Even in ParaCL\n"};

        return l / r;
    }
};

template<>
struct two_child_op<op_type::GR> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::GR) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return (l > r) ? 1 : 0;
    }
};

template<>
struct two_child_op<op_type::GRE> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::GRE) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return (l >= r) ? 1 : 0;
    }
};

template<>
struct two_child_op<op_type::BL> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::BL) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return (l < r) ? 1 : 0;
    }
};

template<>
struct two_child_op<op_type::BLE> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::BLE) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return (l <= r) ? 1 : 0;
    }
};

template<>
struct two_child_op<op_type::EQ> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::EQ) {}

    int execute() const override {
        int l = l_->execute();
        int r = r_->execute();

        return (l == r) ? 1 : 0;
    }
};

template<>
struct two_child_op<op_type::ASSIG> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::ASSIG) {}

    int execute() const override {
        int r = r_->execute();
        static_cast<identifier*>(l_)->set_value(r);

        return 0;
    }
};

template<>
struct two_child_op<op_type::IF> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::IF) {}

    int execute() const override {
        int cond = l_->execute();
        if (cond) r_->execute();

        return 0;
    }
};

template<>
struct two_child_op<op_type::WHILE> final : public i_two_child {
    two_child_op(i_node *l = nullptr, i_node *r = nullptr) : i_two_child(l, r, op_type::WHILE) {}

    int execute() const override {
        int cond = l_->execute();
        while (cond) {
            r_->execute();
            cond = l_->execute();
        }

        return 0;
    }
};

} /*namespace detail*/

} /*namespace para_tree*/
