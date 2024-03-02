#pragma once

#include <unordered_map>
#include <stdexcept>
#include <string>

namespace para_symtab {

class symtab {
    std::unordered_map<std::string, int> table_;

public:
    void push_id(const std::string &name, int value = 0) {
        table_.emplace(name, value);
    }

    bool is_visible(const std::string &name) const {
        return table_.find(name) != table_.end();
    }

    void set_value(const std::string &name, int value) {
        auto search = table_.find(name);

        if (search != table_.end()) search->second = value;

        else throw std::runtime_error("Try to set unvisible / not existing var");
    }

    int get_value(const std::string &name) const {
        auto search = table_.find(name);

        if (search != table_.end()) return search->second;

        else throw std::runtime_error("Try to get unvisible / not existing var");
    }
};

} //<-- para_symtab