#pragma once

#include <iostream>
#include <vector>

namespace para_tree {

enum class op_type {
    ADD,
    SUB,
    MUL,
    DIV
};

namespace detail {

struct inode {
//    virtual void execute() const = 0;

    virtual void dump() const = 0;

    virtual ~inode() = default;
};

class scope : public inode {
    std::vector<const inode*> children_;

public:
    scope() = default;

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        for (auto i : children_) {
            std::cout << i << " ";
            std::cout << typeid(*i).name() << std::endl;
        }

        std::cout << std::endl;
    }

    void add_child(const inode* chld) {
        children_.push_back(chld);
    }
};

class num : public inode {
    int val_;

public:
    num(int val) : val_(val) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val = " << val_ << std::endl << std::endl;
    }
};

class op : public inode {
    op_type type_;
    inode *l_, *r_;

public:
    op(op_type type, inode *l = nullptr, inode *r = nullptr) : type_(type), l_(l), r_(r) {}

    void dump() const override {
        std::cout << "DUMP\ntype " << static_cast<int>(type_) << " " << this << " " << typeid(*this).name() << std::endl;

        if (l_) {
            std::cout << "left  " << l_ << " ";
            std::cout << typeid(*l_).name() << std::endl;
        }
        if (r_) {
            std::cout << "right " << r_ << " ";
            std::cout << typeid(*r_).name() << std::endl << std::endl;
        }

        std::cout << std::endl;
    }

    void setl(inode* node) { l_ = node; }
    void setr(inode* node) { r_ = node; }
};

}

}