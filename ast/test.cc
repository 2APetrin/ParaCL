#include "tree.hpp"

int main() {
    para_tree::ast_tree tree{};

    auto t0 = tree.make_scope();
    auto t1 = tree.make_identifier("COCK", t0);
    auto t2 = tree.make_number(2);
    auto t3 = tree.make_ed_op<para_tree::op_type::ASSIG>(t1, t2);

    //t3->dump();

    auto psh = dynamic_cast<para_tree::detail::i_executable*>(t3);
    t0->add_child(psh);
    //t0->dump_cont();

    tree.set_root(t0);

    auto t5 = tree.make_scope();
    t0->add_child(t5);
    t1 = tree.make_identifier("COCK2", t5);
    t2 = tree.make_number(-6);
    t3 = tree.make_ed_op<para_tree::op_type::ASSIG>(t1, t2);
    t5->add_child(t3);


    tree.dump_cont();
    tree.graphviz_dump();
}