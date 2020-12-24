#include <lab/tree/tree_iterator.hpp>

lab::TreeIterator::TreeIterator(lab::Node* root)
        :value(nullptr), st() {
    fillStack(root);
}

void lab::TreeIterator::fillStack(lab::Node* node) {
    while (node != nullptr) {
        st.push(node);
        node = node->left;
    }
}

void lab::TreeIterator::next() {
    if (!st.is_empty()) {
        Node* current = st.top();
        st.pop();

        if (current != nullptr) {
            fillStack(current->right);
        }

        value = current->value;

        return;
    }

    value = nullptr;
}

bool lab::TreeIterator::hasNext() const {
    return !st.is_empty();
}

lab::ATM* lab::TreeIterator::operator*() {
    return value;
}
