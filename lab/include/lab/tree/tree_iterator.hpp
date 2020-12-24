#ifndef OOP_LABS_TREE_ITERATOR_HPP
#define OOP_LABS_TREE_ITERATOR_HPP

#include <common/stack.hpp>
#include "node.hpp"

namespace lab {
    class TreeIterator {
        public:
            Stack<Node*> st;
            TreeIterator(Node* root);

            void fillStack(Node* node);

            void next();
            bool hasNext() const;

            ATM* operator*();
        private:
            ATM* value;
    };
}

#endif //OOP_LABS_TREE_ITERATOR_HPP
