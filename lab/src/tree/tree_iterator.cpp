#include <lab/tree/tree_iterator.hpp>

lab::TreeIterator::TreeIterator(lab::Node* root) {
    value = nullptr;
    fillStack(root);
}

void lab::TreeIterator::fillStack(lab::Node* node) {
    while (node != nullptr) {
        st.push(node);
        node = node->left;
    }

    next();
}

void lab::TreeIterator::next() {
    Node* current = st.top();
    st.pop();

    if (current != nullptr) {
        fillStack(current->right);
    }

    value = current->value;
}

bool lab::TreeIterator::hasNext() {
    return !st.empty();
}

lab::ATM* lab::TreeIterator::operator*() {
    return value;
}
