#include <common/string.hpp>

common::string::string() {
    m_length = 0;
    m_string = new char[1]{ '\0' };
}

common::string::string(char c) {
    m_length = 1;
    m_string = new char[2]{ c, '\0' };
}

common::string::string(const char* c) {
    if (c) {
        unsigned n = 0;
        while (c[n] != '\0') n++;
        m_length = n;
        m_string = new char[n + 1];
        for (unsigned j = 0; j < n; j++)
            m_string[j] = c[j];

        m_string[n] = '\0';
    }
    else {
        throw std::runtime_error("Char* not provided");
    }
}

common::string::string(const string& s) {
    m_length = s.len();
    m_string = new char[m_length + 1];

    for (unsigned j = 0; j < m_length; j++)
        m_string[j] = s[j];

    m_string[m_length] = '\0';
}

common::string::string(const std::string& s) {
    m_length = s.length();
    m_string = new char[m_length + 1];

    for (unsigned j = 0; j < m_length; j++)
        m_string[j] = s[j];

    m_string[m_length] = '\0';
}

common::string::~string() {
    delete[] m_string;
}

unsigned common::string::len() const {
    return m_length;
}

int common::string::index(char c) const {
    for (unsigned j = 0; j < m_length; j++)
        if (m_string[j] == c) return (int)j;
    return -1;
}

void common::string::upcase(unsigned first, unsigned last) {
    if (first >= last) {
        throw std::runtime_error("Out of range");
    }

    if (last > m_length) {
        throw std::runtime_error("Out of range");
    }

    for (unsigned j = first; j < last; j++)
        if ('a' <= m_string[j] && m_string[j] <= 'z')
            m_string[j] -= ('a' - 'A');
}

void common::string::downcase(unsigned first, unsigned last) {
    if (first >= last) {
        throw std::exception();
    }

    if (last > m_length) {
        throw std::exception();
    }

    for (unsigned j = first; j < last; j++)
        if ('A' <= m_string[j] && m_string[j] <= 'Z')
            m_string[j] += ('a' - 'A');
}

void common::string::togglecase(unsigned first, unsigned last) {
    if (first >= last) {
        throw std::exception();
    }

    if (last > m_length) {
        throw std::exception();
    }

    for (unsigned j = first; j < last; j++)
        if ('A' <= m_string[j] && m_string[j] <= 'Z')
            m_string[j] += ('a' - 'A');
        else if ('a' <= m_string[j] && m_string[j] <= 'z')
            m_string[j] -= ('a' - 'A');
}

std::ostream& common::operator<<(std::ostream& os, const string& s) {
    if (s.len() > 0) {
        for (unsigned j = 0; j < s.len(); j++)
            os << s[j];
    }
    else os << "";

    return os;
}

std::istream& common::operator>>(std::istream& is, string& s) {
    char* c = new char[1000];
    is >> c;
    s = common::string(c);
    delete[] c;

    return is;
}

char common::string::operator[](unsigned j) const {
    if (j >= m_length) throw std::runtime_error("Out of range");
    return m_string[j];
}

char& common::string::operator[](unsigned j) {
    if (j >= m_length) throw std::runtime_error("Out of range");
    return m_string[j];
}

const char* common::string::c_str() const noexcept {
    return m_string;
}

common::string& common::string::operator=(const string& s) {
    if (this == &s) return *this;

    delete[] m_string;
    m_length = s.len();
    m_string = new char[m_length];
    for (unsigned j = 0; j < m_length; j++)
        m_string[j] = s[j];
    return *this;
}

common::string& common::string::operator+=(const string& s) {
    unsigned len = m_length + s.len();
    char* str = new char[len + 1];

    for (unsigned j = 0; j < m_length; j++)
        str[j] = m_string[j];

    for (unsigned i = 0; i < s.len(); i++)
        str[m_length + i] = s[i];

    str[len] = '\0';

    delete[] m_string;
    m_length = len;
    m_string = str;
    return *this;
}

common::string common::operator+(const string& lhs, const string& rhs) {
    return common::string(lhs) += common::string(rhs);
}

common::string common::operator+(const string& lhs, char rhs) {
    return common::string(lhs) += common::string(rhs);
}

common::string common::operator+(const string& lhs, const char* rhs) {
    return common::string(lhs) += common::string(rhs);
}

common::string common::operator+(char lhs, const string& rhs) {
    return common::string(lhs) += rhs;
}

common::string common::operator+(const char* lhs, const string& rhs) {
    return common::string(lhs) += rhs;
}

bool common::operator==(const string& lhs, const string& rhs) {
    if (lhs.len() != rhs.len()) return false;

    unsigned cap = lhs.len();
    unsigned n = 0;
    while ((n < cap) && (lhs[n] == rhs[n])) n++;
    return (n == cap);
}

bool common::operator==(const string& lhs, char rhs) {
    return (lhs == string(rhs));
}

bool common::operator==(const string& lhs, const char* rhs) {
    return (lhs == string(rhs));
}

bool common::operator==(char lhs, const string& rhs) {
    return (string(lhs) == rhs);
}

bool common::operator==(const char* lhs, const string& rhs) {
    return (string(lhs) == rhs);
}

bool common::operator!=(const string& lhs, const string& rhs) {
    return !(lhs == rhs);
}

bool common::operator!=(const string& lhs, char rhs) {
    return !(lhs == rhs);
}

bool common::operator!=(const string& lhs, const char* rhs) {
    return !(lhs == rhs);
}

bool common::operator!=(char lhs, const string& rhs) {
    return !(lhs == rhs);
}

bool common::operator!=(const char* lhs, const string& rhs) {
    return !(lhs == rhs);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

bool common::operator>(const string& lhs, const string& rhs) {
    unsigned cap = (lhs.len() < rhs.len()) ? lhs.len() : rhs.len();
    unsigned n = 0;
    while ((n < cap) && (lhs[n] == rhs[n])) n++;
    if (n == cap) return (lhs.len() > rhs.len());

    if ((('A' <= lhs[n] && lhs[n] <= 'Z') || ('a' <= lhs[n] && lhs[n] <= 'z')) &&
            (('A' <= rhs[n] && rhs[n] <= 'Z') || ('a' <= rhs[n] && rhs[n] <= 'z'))) {
        char A = (char)(lhs[n] & ~32);
        char B = (char)(rhs[n] & ~32);
        if (A != B) return (A > B);
    }
    return lhs[n] > rhs[n];
}

#pragma clang diagnostic pop

bool common::operator>(const string& lhs, char rhs) {
    return (lhs > string(rhs));
}

bool common::operator>(const string& lhs, const char* rhs) {
    return (lhs > string(rhs));
}

bool common::operator>(char lhs, const string& rhs) {
    return (string(lhs) > rhs);
}

bool common::operator>(const char* lhs, const string& rhs) {
    return (string(lhs) > rhs);
}

bool common::operator>=(const string& lhs, const string& rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

bool common::operator>=(const string& lhs, char rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

bool common::operator>=(const string& lhs, const char* rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

bool common::operator>=(char lhs, const string& rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

bool common::operator>=(const char* lhs, const string& rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

bool common::operator<(const string& lhs, const string& rhs) {
    return !(lhs == rhs) && !(lhs > rhs);
}

bool common::operator<(const string& lhs, char rhs) {
    return !(lhs == rhs) && !(lhs > rhs);
}

bool common::operator<(const string& lhs, const char* rhs) {
    return !(lhs == rhs) && !(lhs > rhs);
}

bool common::operator<(char lhs, const string& rhs) {
    return !(lhs == rhs) && !(lhs > rhs);
}

bool common::operator<(const char* lhs, const string& rhs) {
    return !(lhs == rhs) && !(lhs > rhs);
}

bool common::operator<=(const string& lhs, const string& rhs) {
    return !(lhs > rhs);
}

bool common::operator<=(const string& lhs, char rhs) {
    return !(lhs > rhs);
}

bool common::operator<=(const string& lhs, const char* rhs) {
    return !(lhs > rhs);
}

bool common::operator<=(char lhs, const string& rhs) {
    return !(lhs > rhs);
}

bool common::operator<=(const char* lhs, const string& rhs) {
    return !(lhs > rhs);
}