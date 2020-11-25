#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP
#include <type_traits>

namespace common {
    template<class T>
    class Vector {
            using storage_t = std::aligned_storage_t<sizeof(T), alignof(T)>;
        public:
            Vector(int= 4);
            Vector(const Vector&);
            Vector& operator=(const Vector&);
            int capacity() const;
            int length() const;
            T& operator[](int);
            bool operator==(int);
            void push_back(T);
            void clear();
            void create(const int& i);
            void remove(const int& i);
            void resize(const int& n);
            ~Vector<T>();
        private:
            storage_t* m_container;
            int m_lenght{};
            int m_capacity{};
    };
}

template<class T>
common::Vector<T>::Vector(int n) {
    create(n);
}

template<class T>
common::Vector<T>::~Vector() {
    for (int i = 0; i < m_lenght; i++) {
        auto& old_T = reinterpret_cast<T&>(m_container[i]);
        old_T.~T();
    }

    delete[] m_container;
}

template<class T>
int common::Vector<T>::length() const {
    return m_lenght;
}

template<class T>
T& common::Vector<T>::operator[](int i) {
    return reinterpret_cast<T&>(m_container[i]);
}

template<class T>
bool common::Vector<T>::operator==(int) {
    return false;
}

template<class T>
common::Vector<T>& common::Vector<T>::operator=(const Vector& a) {
    if (this == &a) {
        return *this;
    }

    m_lenght = a.m_lenght;

    for (int i = 0; i != a.m_lenght; ++i) {
        auto& old_T = reinterpret_cast<T&>(m_container[i]);
        if (i < a.m_lenght) {
            old_T.~T();
        }

        new(&m_container[m_lenght])T(*reinterpret_cast<T*>(&a.m_container[i]));
    }
    return *this;
}

template<class T>
common::Vector<T>::Vector(const Vector& a) {
    this->m_lenght = a.m_lenght;
    for (int i = 0; i != a.m_lenght; ++i) {
        new(&m_container[m_lenght])T(*reinterpret_cast<T*>(&a.m_container[i]));
    }
}

template<class T>
void common::Vector<T>::push_back(T val) {
    storage_t* newdata;

    if (m_lenght > m_capacity) {
        m_capacity = m_capacity * 2;
        newdata = new storage_t[m_capacity];

        for (int i = 0; i < m_lenght; i++) {
            auto& old_T = reinterpret_cast<T&>(m_container[i]);
            new(&newdata[i])T(old_T);

            old_T.~T();
        }

        delete[] m_container;
        m_container = newdata;
    }

    new(&m_container[m_lenght])T(*reinterpret_cast<T*>(&val));
    m_lenght++;
}

template<class T>
int common::Vector<T>::capacity() const {
    return m_capacity;
}

template<class T>
void common::Vector<T>::remove(const int& i) {
    auto* newdata = new storage_t[m_capacity];
    bool f = false;

    for (int j = 0; j < this->m_lenght; j++) {
        if (j == i) {
            f = true;
        }
        if (f) {
            auto& old_T = reinterpret_cast<T&>(m_container[j]);

            new(&newdata[j - 1])T(old_T);

            old_T.~T();
        }
        else {
            new(&newdata[j])T(*reinterpret_cast<T*>(&m_container[j]));
        }
    }
    this->m_lenght -= 1;
    delete[] this->m_container;
    this->m_container = newdata;
}

template<class T>
void common::Vector<T>::resize(const int& n) {
    auto* newdata = new storage_t[n];
    this->m_capacity = n;
    this->m_lenght = n > this->m_lenght ? this->m_lenght : n;
    for (int i = 0; i < this->m_lenght; i++) {
        auto& old_T = reinterpret_cast<T&>(m_container[i]);

        new(&newdata[i])T(old_T);

        old_T.~T();
    }
    delete[] this->m_container;
    this->m_container = newdata;
}

template<class T>
void common::Vector<T>::clear() {

    for (int i = 0; i < this->m_lenght; i++) {
        auto& old_T = reinterpret_cast<T&>(m_container[i]);
        old_T.~T();
    }

    delete[] this->m_container;
    this->m_lenght = 0;
    this->m_capacity = 1;
    this->m_container = new storage_t[1];
}

template<class T>
void common::Vector<T>::create(const int& i) {
    if (this->m_container) {
        for (int j = 0; j < this->m_lenght; j++) {
            auto& old_T = reinterpret_cast<T&>(m_container[j]);
            old_T.~T();
        }

        delete[] m_container;
    }
    m_lenght = 0;
    m_capacity = i;
    m_container = new storage_t[i];
}

#endif //COMMON_VECTOR_HPP