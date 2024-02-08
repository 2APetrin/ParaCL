#include "iostream"
#include "vector"

namespace detail {

    struct inode {
        int type;
        std::vector<inode*> children;

        virtual void add_child(const inode*) const = 0;

        virtual ~inode() = default;
    };

    struct node : public inode {
        void add_child(const inode*) const override {
            std::cout << "worked" << std::endl;
        }

        node() = default;
    };

}

