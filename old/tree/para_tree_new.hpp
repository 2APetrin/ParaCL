#pragma once

#include <iostream>
#include <vector>
#include "grammar.tab.hh"

namespace para_tree {


struct inode {
    //virtual void execute() const = 0;
    virtual void dump()    const = 0;
    virtual     ~inode() = default;
};

//-----------------------------------------
class num final : public inode {
    int val_;

public:
    num(int val) : val_(val) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val="  << val_ << std::endl << std::endl;
    }
};

//-----------------------------------------
class id final : public inode {
    std::string name_;

public:
    id(std::string str) : name_(str) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var_name=" << name_ << std::endl << std::endl;
    }
};

//-----------------------------------------
class scope final : public inode {
    std::vector<const inode*> children_;

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

    void add_child(const inode* chld) { children_.push_back(chld); }
};

//-----------------------------------------
using tok_type = yy::parser::token_kind_type;
template <tok_type type>
class op final: public inode {
    tok_type type_;
    inode *l_, *r_;

public:
    op(inode *l, inode *r) : type_(type), l_(l), r_(r) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "type=" << type_ << std::endl << std::endl;

        if (l_) {
            std::cout << "left  " << l_ << " ";
            std::cout << typeid(*l_).name() << std::endl;
            l_->dump();
        }
        if (r_) {
            std::cout << "right " << r_ << " ";
            std::cout << typeid(*r_).name() << std::endl << std::endl;
            r_->dump();
        }

        std::cout << std::endl;
    }

    void setl(inode* node) { l_ = node; }
    void setr(inode* node) { r_ = node; }
};

}