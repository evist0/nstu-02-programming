#include <iostream>

template<typename T> class Stack {
        friend void print(const Stack& obj, std::ostream& os) {
            Node* curr = obj.head;
            while (curr) {
                os << curr->data << "  ";
                curr = curr->next;
            }
            os << "\n\n";
        }

    private:
        struct Node {
            T data;
            Node* next;

            Node()
                    :data(), next(nullptr) {
            }

            Node(const T& t)
                    :data(t), next(nullptr) {
            }
        };

        Node* head;
        size_t length;

        void copy_helper(Node*&, Node*);
        void delete_helper(Node*);

    public:

        Stack();
        Stack(const Stack&);
        Stack& operator=(Stack);
        ~Stack();

        void swap(Stack& rhs);

        Stack& push(const T&);
        Stack& pop();
        T& top();


        bool is_empty() const {
            return head ? 0 : 1;
        }

        size_t size() const {
            return length;
        }
};

template<typename T> Stack<T>::Stack()
        :head(nullptr), length(0) {
}

template<typename T> Stack<T>::Stack(const Stack& rhs)
        :head(nullptr),
         length(rhs.length) {
    if (rhs.head) { copy_helper(head, rhs.head); }
}

template<typename T> Stack<T>& Stack<T>::operator=(Stack rhs) {
    swap(rhs);
    return *this;
}

template<typename T> Stack<T>::~Stack() {
    if (head) { delete_helper(head); }
}

template<typename T> void Stack<T>::swap(Stack& rhs) {
    using std::swap;
    swap(head, rhs.head);
    swap(length, rhs.length);
}

template<typename T> Stack<T>& Stack<T>::push(const T& obj) {
    Node* new_node = new Node(obj);
    if (!head) {
        head = new_node;
    }
    else {
        Node* temp = head;
        new_node->next = temp;
        head = new_node;
    }
    ++length;
    return *this;
}

template<typename T> Stack<T>& Stack<T>::pop() {
    if (!head) {
        std::cout << "stack is empty" << std::endl;
    }
    else if (head && !(head->next)) {
        delete head;
        head = nullptr;
        length = 0;
    }
    else {
        Node* temp = head->next;
        head->next = nullptr;
        delete head;
        head = temp;
        --length;
    }
    return *this;
}

template<typename T> T& Stack<T>::top() {
    return head->data;
}

template<typename T> void Stack<T>::copy_helper(Node*& target, Node* source) {
    Node* creator = new Node(source->data);
    Node* iterator = source->next;
    target = creator;
    while (iterator) {
        creator->next = new Node(iterator->data);
        creator = creator->next;
        iterator = iterator->next;
    }
}

template<typename T> void Stack<T>::delete_helper(Node* curr) {
    while (curr) {
        Node* delptr = curr;
        curr = curr->next;
        delptr->next = nullptr;
        delete delptr;
    }
}