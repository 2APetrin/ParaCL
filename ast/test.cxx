#include "tree.hpp"

int main() {
    // auto curr = new para_tree::detail::para_operator<para_tree::op_type::ADD>{nullptr, nullptr};

    // curr->dump();
    // curr->execute();

    // auto sec = new para_tree::detail::para_operator<para_tree::op_type::DIV>{};

    // sec->dump();
    // sec->execute();

    para_tree::ast_tree tree{};

    auto thrd = tree.make_op<para_tree::op_type::SUB>();
    thrd->dump();
    tree.dump_cont();

    std::cout << sizeof(para_tree::detail::two_arg);

    return 0;
}