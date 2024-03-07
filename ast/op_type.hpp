#pragma once

namespace para_tree {

enum class op_type {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    GR,
    GRE,
    BL,
    BLE,
    EQ,
    NEQ,

    SCAN,
    PRINT,
    ASSIG,

    IF,
    IF_ELSE,
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