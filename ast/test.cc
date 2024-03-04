#include <iostream>

int main() {
    // para_tree::ast_tree tree{};

    // auto t0 = tree.make_scope();
    // auto t1 = tree.make_identifier("COCK", static_cast<ptd::scope*>(t0));
    // auto t2 = tree.make_number(2);
    // auto t3 = tree.make_d_op<para_tree::op_type::ASSIG>(t1, t2);

    // static_cast<ptd::scope*>(t0)->add_child(t3);

    // tree.set_root(static_cast<ptd::scope*>(t0));

    // auto t6 = tree.make_identifier("COCK", static_cast<ptd::scope*>(t0));

    // auto t5 = tree.make_s_op<pt::op_type::PRINT>(t6);
    // static_cast<ptd::scope*>(t0)->add_child(t5);

    // tree.dump_cont();
    // tree.graphviz_dump();

    // tree.execute_tree();
    int a = 0;

    int b = a = 7;

    std::cout << b << std::endl;
}