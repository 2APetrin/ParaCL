#pragma once

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
    PRINT,
    ASSIG,

    IF,
    WHILE,

    AND,
    OR,
    XOR,
    NOT,

    UNARY_PLUS,
    UNARY_MINUS,

    ERROR = -1
};

}