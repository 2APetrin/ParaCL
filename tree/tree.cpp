#include "para_tree.hpp"

int main() {
    para_tree::detail::num n1{1};
    para_tree::detail::num n2{2};
    para_tree::detail::op  op{para_tree::op_type::ADD, &n1, &n2};

    op.dump();
    n1.dump();
    n2.dump();

    return 0;
}