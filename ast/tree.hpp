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
    ast_tree() = default;

//---------------------------------------------------------------------
    /**make executable double child operator*/
    template <op_type type>
    detail::exec_d_op<type>* make_ed_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        detail::exec_d_op<type>* node = new detail::exec_d_op<type>{l, r, type};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);

        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::exec_d_op<type>*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    /**make executable single child operator*/
    template <op_type type>
    detail::exec_s_op<type>* make_es_op(node_ptr chld = nullptr) {
        detail::exec_s_op<type>* node = new detail::exec_s_op<type>{chld, type};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);

        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::exec_s_op<type>*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    /**make calculatable double child operator*/
    template <op_type type>
    detail::calc_d_op<type>* make_cd_op(node_ptr l = nullptr, node_ptr r = nullptr) {
        detail::calc_d_op<type>* node = new detail::calc_d_op<type>{l, r, type};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);

        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::calc_d_op<type>*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    detail::number* make_number(int val) {
        detail::number* node = new detail::number{val};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::number*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    detail::identifier* make_identifier(std::string str, detail::scope* scp = nullptr) {
        detail::identifier* node = new detail::identifier{str, scp};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::identifier*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    detail::scope* make_scope(detail::scope* parent_scope = nullptr) {
        detail::scope* node = new detail::scope{parent_scope};

        node_ptr base_node_ptr = static_cast<node_ptr>(node);
        std::unique_ptr<detail::i_node> push = std::unique_ptr<detail::i_node>{base_node_ptr};

        node_container_.push_back(std::move(push));

        auto last_inode = node_container_.back().get();
        auto ret = dynamic_cast<detail::scope*>(last_inode);

        return ret;
    }

//---------------------------------------------------------------------
    int execute_tree() const              { root_->execute(); }
    void set_root(detail::scope* newroot) { root_ = newroot;  }

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