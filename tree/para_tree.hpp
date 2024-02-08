#pragma once

#include <iostream>
#include <vector>

namespace para_tree {

enum class node_type {
    SCOPE,

    ADD,
    SUB,
    MUL,
    DIV,

    SCAN,
    ASSIG,

    IF,
    WHILE,

    GR,
    GRE,
    BL,
    BLE,
    EQ,

    NUMBER,
    ID
};

namespace detail {

class inode {
protected:
    std::vector<const inode*> children_;

public:
    virtual void add_child(const inode* chld) = 0;

    virtual ~inode() = default;
};

struct scope : public inode {
    using inode::children_;

    scope() { std::cout << "ctor worked\n"; }

    void add_child(const inode* chld) override { children_.push_back(chld); std::cout << "push worked\n"; }

    void fuck_srp_dump() {
        std::cout << "\nnode dump:" << std::endl;
        for (auto i : children_)
            std::cout << i << std::endl;
    }
};

}

}