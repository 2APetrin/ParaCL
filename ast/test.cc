#include "tree.hpp"

int main() {
    para_tree::ast_tree tree{};

    auto t0 = tree.make_scope();
    auto t1 = tree.make_number(1);
    auto t2 = tree.make_number(2);
    auto t3 = tree.make_cd_op<para_tree::op_type::ADD>(t1, t2);

    t0->add_child(dynamic_cast<para_tree::detail::i_executable*>(t3));

    tree.set_root(t0);

    tree.graphviz_dump();
}