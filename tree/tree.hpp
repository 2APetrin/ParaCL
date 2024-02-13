#pragma once

#include <iostream>
#include <vector>

namespace para_tree {


struct i_node {
    //virtual void execute() const = 0;
    virtual void dump()    const = 0;
    virtual     ~i_node() = default;
};

//-----------------------------------------//
class num final : public i_node {
    int val_;

public:
    num(int val) : val_(val) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "val=" << val_ << std::endl << std::endl;
    }
};

//-----------------------------------------//
class id final : public i_node {
    std::string name_;

public:
    id(std::string str) : name_(str) {}

    void dump() const override {
        std::cout << "DUMP " << this << " " << typeid(*this).name() << std::endl;
        std::cout << "var_name=" << name_ << std::endl << std::endl;
    }
};

//-----------------------------------------//
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
};

//-----------------------------------------//
template <int type>
class 

}