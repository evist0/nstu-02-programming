#ifndef OOP_LABS_NODE_HPP
#define OOP_LABS_NODE_HPP

#include <lab/atm/kinds/atm.hpp>

namespace lab {
    class Node {
        public:
            Node(ATM* value);
            ~Node();
        private:
            ATM* value;
            Node* left;
            Node* right;

            friend class Tree;
            friend class TreeIterator;
    };
}

#endif //OOP_LABS_NODE_HPP
