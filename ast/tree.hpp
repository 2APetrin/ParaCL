#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <memory>
#include "node.hpp"

namespace para_tree {

static int img_count = 0;

class ast_tree final : private detail::node_manager {
    using node_ptr = detail::i_node*;

    using detail::node_manager::node_container_;
    node_ptr root_;

public:
    ast_tree() = default;

//---------------------------------------------------------------------
    template <op_type type>
    node_ptr make_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        detail::para_operator<type>* node = new detail::para_operator<type>{l, r};
        node_ptr base_node_ptr = static_cast<node_ptr>(node);

        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_number(int val) {
        detail::number* node = new detail::number{val};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_identifier(std::string str, detail::scope* scp = nullptr) {
        detail::identifier* node = new detail::identifier{str, scp};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
    node_ptr make_scope(detail::scope* parent_scope = nullptr) {
        detail::scope* node = new detail::scope{parent_scope};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        return node_container_.back().get();
    }

//---------------------------------------------------------------------
//    int execute_tree() const { }

//----------------------------------GRAPHVIZ----------------------------------
    void set_root(node_ptr newroot) { root_ = newroot; }

    void dump_cont() const {
        std::cout << "CONTAINER DUMP\n";
        for (auto i = node_container_.begin(), e = node_container_.end(); i != e; ++i) {
            (*i)->execute();
            std::cout << " " << *i << "\n";
        }
    }

    void graphviz_dump() const {
        std::ofstream out;
        open_grapviz(out);

        root_->graphviz_dump(out);

        close_graphviz(out);

        char sys_cmd[200] = "dot ../ast/logs/log_graphviz.dot -Tpng -o ../ast/logs/images/tree_dump";
        snprintf(sys_cmd + strlen(sys_cmd), 30, "%d.png", img_count);
        system(sys_cmd);

        std::cout << "COMMAND=" << sys_cmd << std::endl;

        std::cout << img_count << " dump made\n";
        img_count++;
    }

//---------------------------------------------------------------------
private:
    int open_grapviz(std::ofstream &out) const {
        out.open("../ast/logs/log_graphviz.dot");

        if (!out.is_open()) {
            std::cerr << "Cannot open graphviz file. Programm shutdown\n";
            return 1;
        }

        out << "digraph\n{\n";
        return 0;
    }


    void close_graphviz(std::ofstream &out) const {
        out << "}";
        out.close();
    }
};

} /*namespace para tree*/