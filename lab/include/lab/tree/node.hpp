#ifndef OOP_LABS_NODE_HPP
#define OOP_LABS_NODE_HPP

#include <lab/atm/kinds/atm.hpp>

namespace lab {
    template<typename T> class Node {
        public:
            Node(T value);
            ~Node();
        private:
            T value;
            Node<T>* left;
            Node<T>* right;

            template<typename U> friend class Tree;
            template<typename Z> friend class TreeIterator;
    };
}

template<typename T> lab::Node<T>::Node(T value)
        :value(new T(value)), left(nullptr), right(nullptr) {
}

template<typename T> lab::Node<T>::~Node() {
    delete value;
}

#endif //OOP_LABS_NODE_HPP
