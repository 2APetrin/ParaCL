#include "tree.hpp"

int main() {
    // auto curr = new para_tree::detail::para_operator<para_tree::op_type::ADD>{nullptr, nullptr};

    // curr->dump();
    // curr->execute();

    // auto sec = new para_tree::detail::para_operator<para_tree::op_type::DIV>{};

    // sec->dump();
    // sec->execute();

    para_tree::ast_tree tree{};

    auto n1 = static_cast<para_tree::detail::op_base*>(tree.make_op<para_tree::op_type::SUB>());
    auto n2 = tree.make_number(5);
    auto n3 = tree.make_number(3);

    n2->dump();
    n3->dump();

    n1->setl(n2);
    n1->setr(n3);

    tree.set_root(n1);

    n1->dump();

    tree.dump_cont();

    return 0;
}