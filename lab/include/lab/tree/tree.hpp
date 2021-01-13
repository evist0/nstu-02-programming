#ifndef OOP_LABS_TREE_HPP
#define OOP_LABS_TREE_HPP

#include <lab/atm/atm_io.hpp>
#include "node.hpp"
#include "tree_iterator.hpp"

namespace lab {
    template<typename T> class Tree {
        public:
            Tree() noexcept;
            ~Tree();

            TreeIterator<T> begin();

            void insert(T obj);
            T* search(const common::string& id);
            T* search(const T& value);
            void erase(const common::string& id);
            void erase(const T& value);
            bool empty();
            void clear();

            static Tree<T> read(std::ifstream& ifstream);
            void write(std::ofstream& ostream);

        private:
            static void destroy_tree(Node<T>*& leaf);
            static void insert(T obj, Node<T>* leaf);
            static Node<T>* search(const common::string& id, Node<T>* leaf);
            static Node<T>* search(const T& value, Node<T>* leaf);

            Node<T>* root;
    };
}

template<typename T> lab::Tree<T>::Tree() noexcept
        :root(nullptr) {
}

template<typename T> void lab::Tree<T>::insert(T obj) {
    if (root != nullptr) {
        insert(obj, root);
    }

    else {
        root = new Node<T>(obj);
    }
}

template<typename T> T* lab::Tree<T>::search(const common::string& id) {
    return search(id, root)->value;
}

template<typename T> T* lab::Tree<T>::search(const T& value) {
    return search(value, root)->value;
}

template<typename T> void lab::Tree<T>::erase(const common::string& id) {
    auto node_to_delete = search(id, root);

    if (node_to_delete != nullptr) {
        while (node_to_delete->right != nullptr) {
            delete node_to_delete->value;

            node_to_delete->value = node_to_delete->right->value;

            node_to_delete = node_to_delete->right;
        }
    }
}

template<typename T> void lab::Tree<T>::erase(const T& value) {
    auto node_to_delete = search(value, root);

    if (node_to_delete != nullptr) {
        while (node_to_delete->right != nullptr) {
            delete node_to_delete->value;

            node_to_delete->value = node_to_delete->right->value;

            node_to_delete = node_to_delete->right;
        }
    }
}

template<typename T> bool lab::Tree<T>::empty() {
    return root == nullptr;
}

template<typename T> lab::Tree<T>::~Tree() {
    destroy_tree(root);
}

template<typename T> void lab::Tree<T>::destroy_tree(lab::Node<T>*& leaf) {
    if (leaf != nullptr) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
        leaf = nullptr;
    }
}

template<typename T> void lab::Tree<T>::insert(T obj, lab::Node<T>* leaf) {
    if (obj < leaf->value) {
        if (leaf->left != nullptr) {
            insert(obj, leaf->left);
        }

        else {
            leaf->left = new Node<T>(obj);
        }
    }
    else {
        if (leaf->right != nullptr) {
            insert(obj, leaf->right);
        }

        else {
            leaf->right = new Node<T>(obj);
        }
    }
}

template<> lab::Node<lab::ATM*>* lab::Tree<lab::ATM*>::search(const common::string& id, Node<lab::ATM*>* leaf) {
    if (leaf != nullptr) {
        if (id == *(leaf->value)->id())
            return leaf;
        if (id < *(leaf->value)->id())
            return search(id, leaf->left);
        else
            return search(id, leaf->right);
    }
    else return nullptr;
}

template<typename T> lab::Node<T>* lab::Tree<T>::search(const T& value, Node<T>* leaf) {
    if (leaf != nullptr) {
        if (value == *leaf->value)
            return leaf;
        if (value < *leaf->value)
            return search(value, leaf->left);
        else
            return search(value, leaf->right);
    }
    else return nullptr;
}

template<typename T> lab::TreeIterator<T> lab::Tree<T>::begin() {
    return lab::TreeIterator<T>(root);
}

template<typename T> void lab::Tree<T>::clear() {
    lab::Tree<T>::destroy_tree(root);
}

template<>
lab::Tree<int> lab::Tree<int>::read(std::ifstream& ifstream) {
    auto tree = lab::Tree<int>();

    while (ifstream.is_open()) {
        int temp;
        ifstream.read(reinterpret_cast<char*>(&temp), sizeof(int));

        if (!ifstream.eof()) {
            tree.insert(temp);
        }
        else {
            ifstream.close();
        }
    }

    return tree;
}

template<>
lab::Tree<float> lab::Tree<float>::read(std::ifstream& ifstream) {
    auto tree = lab::Tree<float>();

    while (ifstream.is_open()) {
        float temp;
        ifstream.read(reinterpret_cast<char*>(&temp), sizeof(float));

        if (!ifstream.eof()) {
            tree.insert(temp);
        }
        else {
            ifstream.close();
        }
    }

    return tree;
}

template<>
lab::Tree<lab::ATM*> lab::Tree<lab::ATM*>::read(std::ifstream& ifstream) {
    auto tree = lab::Tree<lab::ATM*>();

    while (ifstream.is_open()) {
        auto atm = lab::ATM_io::load_bin(ifstream);

        if (atm != nullptr) {
            tree.insert(atm);
        }
        else {
            ifstream.close();
        }
    }

    return tree;
}

template<>
void lab::Tree<int>::write(std::ofstream& ofstream) {
    auto iterator = this->begin();

    while (iterator.hasNext()) {
        iterator.next();
        ofstream.write(reinterpret_cast<const char*>(*iterator), sizeof(int));
    }
}

template<>
void lab::Tree<float>::write(std::ofstream& ofstream) {
    auto iterator = this->begin();

    while (iterator.hasNext()) {
        iterator.next();
        ofstream.write(reinterpret_cast<const char*>(&iterator), sizeof(float));
    }
}

template<>
void lab::Tree<lab::ATM*>::write(std::ofstream& ofstream) {
    auto atm_iterator = this->begin();

    while (atm_iterator.hasNext()) {
        atm_iterator.next();
        lab::ATM_io::save_bin(ofstream, *atm_iterator);
    }
}

#endif //OOP_LABS_TREE_HPP
