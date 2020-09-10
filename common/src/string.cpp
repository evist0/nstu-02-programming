#include <common/string.hpp>

lab1::string::string() {
		m_length = 0;
		m_string = new char[1] { '\0'};
}

lab1::string::string(char c) {
		m_length = 1;
		m_string = new char[2] { c, '\0'};
}

lab1::string::string(const char* c) {
		if (c) {
				unsigned n = 0;
				while (c[n] != '\0') n++;
				m_length = n;
				m_string = new char[n];
				for (unsigned j = 0; j < n; j++)
						m_string[j] = c[j];
		}
		else {
				m_length = 0;
				m_string = new char[0];
		}
}

lab1::string::string(const string& s) {
		m_length = s.len();
		m_string = new char[m_length];
		for (unsigned j = 0; j < m_length; j++)
				m_string[j] = s[j];
}

lab1::string::string(const std::string& s) {
		m_length = s.length();
		m_string = new char[m_length];
		for (unsigned j = 0; j < m_length; j++)
				m_string[j] = s[j];
}

lab1::string::~string() {
		delete[] m_string;
}

unsigned lab1::string::len() const {
		return m_length;
}

int lab1::string::index(char c) const {
		for (unsigned j = 0; j < m_length; j++)
				if (m_string[j] == c) return (int)j;
		return -1;
}

void lab1::string::upcase(unsigned first, unsigned last) {
		if (first >= last) {
				throw std::runtime_error("Out of range");
		}

		if (last > m_length) {
        std::runtime_error("Out of range");
		}

		for (unsigned j = first; j < last; j++)
				if ('a' <= m_string[j] && m_string[j] <= 'z')
						m_string[j] -= ('a' - 'A');
}

void lab1::string::downcase(unsigned first, unsigned last) {
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

void lab1::string::togglecase(unsigned first, unsigned last) {
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

std::ostream& lab1::operator<<(std::ostream& os, const string& s) {
		if (s.len() > 0) {
				for (unsigned j = 0; j < s.len(); j++)
						os << s[j];
		}
		else os << "";

		return os;
}

std::istream& lab1::operator>>(std::istream& is, string& s) {
		char* c = new char[1000];
		is >> c;
		s = lab1::string(c);
		delete[] c;

		return is;
}

char lab1::string::operator[](unsigned j) const {
		if (j >= m_length) throw std::runtime_error("Out of range");
		return m_string[j];
}

char& lab1::string::operator[](unsigned j) {
		if (j >= m_length) throw std::runtime_error("Out of range");
		return m_string[j];
}

const char* lab1::string::c_str() const noexcept {
		return m_string;
}

lab1::string& lab1::string::operator=(const string& s) {
		if (this == &s) return *this;

		delete[] m_string;
		m_length = s.len();
		m_string = new char[m_length];
		for (unsigned j = 0; j < m_length; j++)
				m_string[j] = s[j];
		return *this;
}

lab1::string& lab1::string::operator+=(const string& s) {
		unsigned len = m_length + s.len();
		char* str = new char[len];

		for (unsigned j = 0; j < m_length; j++)
				str[j] = m_string[j];

		for (unsigned i = 0; i < s.len(); i++)
				str[m_length + i] = s[i];

		delete[] m_string;
		m_length = len;
		m_string = str;
		return *this;
}

lab1::string lab1::operator+(const string& lhs, const string& rhs) {
		return lab1::string(lhs) += lab1::string(rhs);
}

lab1::string lab1::operator+(const string& lhs, char rhs) {
		return lab1::string(lhs) += lab1::string(rhs);
}

lab1::string lab1::operator+(const string& lhs, const char* rhs) {
		return lab1::string(lhs) += lab1::string(rhs);
}

lab1::string lab1::operator+(char lhs, const string& rhs) {
		return lab1::string(lhs) += rhs;
}

lab1::string lab1::operator+(const char* lhs, const string& rhs) {
		return lab1::string(lhs) += rhs;
}

bool lab1::operator==(const string& lhs, const string& rhs) {
		if (lhs.len() != rhs.len()) return false;

		unsigned cap = lhs.len();
		unsigned n = 0;
		while ((n < cap) && (lhs[n] == rhs[n])) n++;
		return (n == cap);
}

bool lab1::operator==(const string& lhs, char rhs) {
		return (lhs == string(rhs));
}

bool lab1::operator==(const string& lhs, const char* rhs) {
		return (lhs == string(rhs));
}

bool lab1::operator==(char lhs, const string& rhs) {
		return (string(lhs) == rhs);
}

bool lab1::operator==(const char* lhs, const string& rhs) {
		return (string(lhs) == rhs);
}

bool lab1::operator!=(const string& lhs, const string& rhs) {
		return !(lhs == rhs);
}

bool lab1::operator!=(const string& lhs, char rhs) {
		return !(lhs == rhs);
}

bool lab1::operator!=(const string& lhs, const char* rhs) {
		return !(lhs == rhs);
}

bool lab1::operator!=(char lhs, const string& rhs) {
		return !(lhs == rhs);
}

bool lab1::operator!=(const char* lhs, const string& rhs) {
		return !(lhs == rhs);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
bool lab1::operator>(const string& lhs, const string& rhs) {
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

bool lab1::operator>(const string& lhs, char rhs) {
		return (lhs > string(rhs));
}

bool lab1::operator>(const string& lhs, const char* rhs) {
		return (lhs > string(rhs));
}

bool lab1::operator>(char lhs, const string& rhs) {
		return (string(lhs) > rhs);
}

bool lab1::operator>(const char* lhs, const string& rhs) {
		return (string(lhs) > rhs);
}

bool lab1::operator>=(const string& lhs, const string& rhs) {
		return (lhs == rhs) || (lhs > rhs);
}

bool lab1::operator>=(const string& lhs, char rhs) {
		return (lhs == rhs) || (lhs > rhs);
}

bool lab1::operator>=(const string& lhs, const char* rhs) {
		return (lhs == rhs) || (lhs > rhs);
}

bool lab1::operator>=(char lhs, const string& rhs) {
		return (lhs == rhs) || (lhs > rhs);
}

bool lab1::operator>=(const char* lhs, const string& rhs) {
		return (lhs == rhs) || (lhs > rhs);
}

bool lab1::operator< (const string& lhs, const string& rhs)
{
		return !(lhs == rhs) && !(lhs > rhs);
}

bool lab1::operator< (const string& lhs, char rhs)
{
		return !(lhs == rhs) && !(lhs > rhs);
}

bool lab1::operator< (const string& lhs, const char* rhs)
{
		return !(lhs == rhs) && !(lhs > rhs);
}

bool lab1::operator< (char lhs, const string& rhs)
{
		return !(lhs == rhs) && !(lhs > rhs);
}

bool lab1::operator< (const char* lhs, const string& rhs)
{
		return !(lhs == rhs) && !(lhs > rhs);
}

bool lab1::operator<= (const string& lhs, const string& rhs)
{
		return !(lhs > rhs);
}

bool lab1::operator<= (const string& lhs, char rhs)
{
		return !(lhs > rhs);
}

bool lab1::operator<= (const string& lhs, const char* rhs)
{
		return !(lhs > rhs);
}

bool lab1::operator<= (char lhs, const string& rhs)
{
		return !(lhs > rhs);
}

bool lab1::operator<= (const char* lhs, const string& rhs)
{
		return !(lhs > rhs);
}