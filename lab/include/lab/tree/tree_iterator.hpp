#ifndef OOP_LABS_TREE_ITERATOR_HPP
#define OOP_LABS_TREE_ITERATOR_HPP

#include <common/stack.hpp>
#include "node.hpp"

namespace lab {
    template<typename T> class TreeIterator {
        public:
            Stack<Node<T>*> st;
            TreeIterator(Node<T>* root);

            void fillStack(Node<T>* node);

            void next();
            bool hasNext() const;

            T operator*();
        private:
            T value;
    };
}

template<typename T> lab::TreeIterator<T>::TreeIterator(lab::Node<T>* root)
        :value(nullptr), st() {
    fillStack(root);
}

template<typename T> void lab::TreeIterator<T>::fillStack(lab::Node<T>* node) {
    while (node != nullptr) {
        st.push(node);
        node = node->left;
    }
}

template<typename T> void lab::TreeIterator<T>::next() {
    if (!st.is_empty()) {
        Node<T>* current = st.top();
        st.pop();

        if (current != nullptr) {
            fillStack(current->right);
        }

        value = current->value;

        return;
    }

    value = nullptr;
}

template<typename T> bool lab::TreeIterator<T>::hasNext() const {
    return !st.is_empty();
}

template<typename T> T lab::TreeIterator<T>::operator*() {
    return value;
}

#endif //OOP_LABS_TREE_ITERATOR_HPP
