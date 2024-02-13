#pragma once

#include <iostream>
#include <vector>

namespace para_tree {

enum class op_type {
    ADD,
    SUB,
    MUL,
    DIV,
    ASSIG
};

struct inode {
//    virtual void execute() const = 0;

    virtual void dump() const = 0;

    virtual ~inode() = default;
};

class scope final : public inode {
    std::vector<const inode*> children_;

public:
    scope() = default;

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        for (auto i : children_) {
            if (i) i->dump();
        }

        std::cout << std::endl;
    }

    void add_child(const inode *chld) {
        std::cout << "CHILD IN TIME=" << chld << std::endl;
        std::cout << "child added" << std::endl;
        children_.push_back(chld);
    }
};

class num final : public inode {
    int val_;

public:
    num(int val) : val_(val) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val = " << val_ << std::endl << std::endl;
    }
};

class op final : public inode {
    op_type type_;
    inode *l_, *r_;

public:
    op(op_type type, inode *l = nullptr, inode *r = nullptr) : type_(type), l_(l), r_(r) {}

    void dump() const override {
        std::cout << "DUMP\ntype " << static_cast<int>(type_) << " " << this << " " << typeid(*this).name() << std::endl;

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


class id final : public inode {
    std::string name_;

public:
    id(const char* name) : name_(name) { std::cout << "id ctor:\n" << name << " " << name_ << std::endl; }

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var name " << name_ << std::endl;

        std::cout << std::endl;
    }
};

}
