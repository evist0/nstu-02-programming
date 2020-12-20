#include <lab/atm/report_container.hpp>

lab::Report_Container::Report_Container()
        :m_container(new Report[4]), m_length(0), m_capacity(4) {

}

lab::Report& lab::Report_Container::operator[](int i) {
    return m_container[i];
}

size_t lab::Report_Container::length() const {
    return m_length;
}

size_t lab::Report_Container::capacity() const {
    return m_capacity;
}

void lab::Report_Container::push_back(lab::Report report) {
    if (m_length + 1 > m_capacity) {
        realloc();
    }

    m_container[this->m_length++] = report;
}

void lab::Report_Container::clear() {
    m_length = 0;
}

void lab::Report_Container::realloc() {
    auto* _copy = new Report[this->m_capacity * 2];

    for (size_t i = 0; i < this->m_length; i++) {
        _copy[i] = m_container[i];
    }

    delete[] m_container;

    m_container = _copy;
}

lab::Report_Container::~Report_Container() {
    delete[] m_container;
}


