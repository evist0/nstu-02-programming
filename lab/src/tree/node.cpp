#include <lab/tree/node.hpp>

lab::Node::Node(ATM* value)
        :value(value), left(nullptr), right(nullptr) {
}

lab::Node::~Node() {
    delete value;
}
