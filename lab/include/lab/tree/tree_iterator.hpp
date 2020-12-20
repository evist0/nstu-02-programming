#ifndef OOP_LABS_TREE_ITERATOR_HPP
#define OOP_LABS_TREE_ITERATOR_HPP

#include <stack>
#include "node.hpp"

namespace lab {
    class TreeIterator {
        public:
            std::stack<Node*> st;
            TreeIterator(Node* root);

            void fillStack(Node* node);

            void next();
            bool hasNext();

            ATM* operator*();
        private:
            ATM* value;
    };
}

#endif //OOP_LABS_TREE_ITERATOR_HPP
