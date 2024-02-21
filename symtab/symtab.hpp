#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>

namespace para_symtab {

class symtab {
    std::unordered_map<std::string, int> table_;

public:
    void push_id(std::string name, int value = 0) {
        table_.emplace(name, value);
    }

    bool is_visible(std::string name) {
        return table_.find(name) != table_.end();
    }

    void set_value(std::string name, int value) {
        auto search = table_.find(name);
    
        if (search != table_.end()) search->second = value;
        
        else throw std::runtime_error("Try to set unvisible / not existing var");
    }
};

} //<-- para_symtab