#include <lab/tree/tree.hpp>

lab::Tree::Tree() noexcept
        :root(nullptr) {
}

void lab::Tree::insert(lab::ATM* atm) {
    if (root != nullptr) {
        insert(atm, root);
    }

    else {
        root = new Node(atm);
    }
}

lab::ATM* lab::Tree::search(const common::string& id) {
    return search(id, root)->value;
}

void lab::Tree::erase(const common::string& id) {
    auto node_to_delete = search(id, root);

    if (node_to_delete != nullptr) {
        while (node_to_delete->right != nullptr) {
            delete node_to_delete->value;

            node_to_delete->value = node_to_delete->right->value;

            node_to_delete = node_to_delete->right;
        }
    }
}

bool lab::Tree::empty() {
    return root == nullptr;
}

lab::Tree::~Tree() {
    destroy_tree(root);
}

void lab::Tree::destroy_tree(lab::Node*& leaf) {
    if (leaf != nullptr) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
        leaf = nullptr;
    }
}

void lab::Tree::insert(lab::ATM* atm, lab::Node* leaf) {
    if (atm->id() < leaf->value->id()) {

        if (leaf->left != nullptr) {
            insert(atm, leaf->left);
        }

        else {
            leaf->left = new Node(atm);
        }

    }
    else {

        if (leaf->right != nullptr) {
            insert(atm, leaf->right);
        }

        else {
            leaf->right = new Node(atm);
        }

    }
}

lab::Node* lab::Tree::search(const common::string& id, Node* leaf) {
    if (leaf != nullptr) {
        if (id == leaf->value->id())
            return leaf;
        if (id < leaf->value->id())
            return search(id, leaf->left);
        else
            return search(id, leaf->right);
    }
    else return nullptr;
}

lab::TreeIterator lab::Tree::begin() {
    return lab::TreeIterator(root);
}

void lab::Tree::clear() {
    lab::Tree::destroy_tree(root);
}
