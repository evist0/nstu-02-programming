#ifndef OOP_LABS_TREE_HPP
#define OOP_LABS_TREE_HPP

#include <lab/atm/atm_io.hpp>
#include "node.hpp"
#include "tree_iterator.hpp"

namespace lab {
    class Tree {
        public:
            Tree();
            ~Tree();

            TreeIterator begin();

            void insert(ATM* atm);
            ATM* search(const common::string& id);
            void erase(const common::string& id);
            bool empty();
            void clear();

        private:
            static void destroy_tree(Node* leaf);
            static void insert(ATM* atm, Node* leaf);
            static Node* search(const common::string& id, Node* leaf);

            Node* root;
    };
}

#endif //OOP_LABS_TREE_HPP
