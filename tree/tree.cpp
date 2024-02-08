#include "para_tree.hpp"

int main() {
    para_tree::detail::scope fst{};

    para_tree::detail::scope snd{};
    para_tree::detail::scope trd{};
    para_tree::detail::scope frd{};

    fst.add_child(static_cast<para_tree::detail::inode*>(&snd));
    fst.fuck_srp_dump();
    fst.add_child(static_cast<para_tree::detail::inode*>(&trd));
    fst.fuck_srp_dump();
    fst.add_child(static_cast<para_tree::detail::inode*>(&frd));
    fst.fuck_srp_dump();

    std::cout << sizeof(para_tree::detail::scope);

    return 0;
}