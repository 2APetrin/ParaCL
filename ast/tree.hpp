#pragma once

#include "node.hpp"
#include <cstring>
#include <memory>

namespace para_tree {

namespace detail {

//---------------------------rule of zero---------------------------
class node_manager {
protected:
    std::vector<std::unique_ptr<i_node>> node_container_;

protected:
    node_manager()  = default;
    ~node_manager() = default;

    node_manager            (const node_manager&) = delete;
    node_manager& operator= (const node_manager&) = delete;
    node_manager            (node_manager&&) = delete;
    node_manager& operator= (node_manager&&) = delete;
};

} /*namespace detail*/

static int img_count = 0;

//-------------------------------ast_tree-------------------------------
class ast_tree final : private detail::node_manager {
    using node_ptr = detail::i_node*;
    using detail::node_manager::node_container_;

    detail::scope* root_;

public:
    bool is_ok = true;

    ast_tree() = default;

//---------------------------------------------------------------------
    /**make three child operator*/
    template <op_type T>
    detail::i_three_child* make_t_op(node_ptr fst, node_ptr snd, node_ptr trd) {
        node_ptr node = create_unique_push_get_ptr(new detail::three_child_op<T>{fst, snd, trd});

        return static_cast<detail::i_three_child*>(node);
    }

//---------------------------------------------------------------------
    /**make two children operator*/
    template <op_type T>
    detail::i_two_child* make_d_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        node_ptr node = create_unique_push_get_ptr(new detail::two_child_op<T>{l, r});

        return static_cast<detail::i_two_child*>(node);
    }

//---------------------------------------------------------------------
    /**make single child operator*/
    template <op_type T>
    detail::i_one_child* make_s_op(node_ptr chld = nullptr) {
        node_ptr node = create_unique_push_get_ptr(new detail::one_child_op<T>{chld});

        return static_cast<detail::i_one_child*>(node);
    }

//---------------------------------------------------------------------
    node_ptr make_number(int val) {
        return create_unique_push_get_ptr(new detail::number{val});
    }

//---------------------------------------------------------------------
    node_ptr make_nop() {
        return create_unique_push_get_ptr(new detail::nop{});
    }

//---------------------------------------------------------------------
    node_ptr make_identifier(std::string str, detail::scope* scp = nullptr) {
        return create_unique_push_get_ptr(new detail::identifier{str, scp});
    }

//---------------------------------------------------------------------
    node_ptr make_scope(detail::scope* parent_scope = nullptr) {
        return create_unique_push_get_ptr(new detail::scope{parent_scope});
    }

    node_ptr make_scan() {
        return create_unique_push_get_ptr(new detail::scan{});
    }

private:
    node_ptr create_unique_push_get_ptr(node_ptr node) {
        node_container_.push_back(std::move(std::unique_ptr<detail::i_node>{node}));

        return node_container_.back().get();
    }


public:

//---------------------------------------------------------------------
    int execute_tree() const {
        if (is_ok) 
            return root_->execute(); 
        throw std::runtime_error("Compilation error. Check messages upper.");
    }
    void set_root(detail::scope* newroot) { root_ = newroot;         }

//----------------------------------GRAPHVIZ----------------------------------
    void dump_cont() const {
        std::cout << "CONTAINER DUMP\n";
        for (auto i = node_container_.begin(), e = node_container_.end(); i != e; ++i) {
            (*i)->dump();
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

} /*namespace para_tree*/