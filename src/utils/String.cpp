#include <String.h>

using namespace Utils;

String::String() {
		_length = 0;
		_string = new char[0];
}

String::String(char c) {
		_length = 0;
		_string = new char(c);
}

String::String(const char* c) {
		if (c) {
				unsigned n = 0;
				while (c[n] != '\0') n++;
				_length = n;
				_string = new char[n];
				for (unsigned j = 0; j < n; j++)
						_string[j] = c[j];
		}
		else {
				_length = 0;
				_string = new char[0];
		}
}

String::String(const String& s) {
		_length = s.len();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
}

String::String(const std::string& s) {
		_length = s.length();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
}

String::~String() {
		delete[] _string;
}

unsigned String::len() const {
		return _length;
}

int String::index (char c) const
{
		for (unsigned j=0; j < _length; j++)
				if (_string[j] == c) return (int)j;
		return -1;
}

void String::upcase(unsigned first, unsigned last) {
		if(first >= last) {
				throw std::exception("First is greater than or equal to last");
		}

		if (last > _length) {
				throw std::exception("Last is greater than length");
		}

		for (unsigned j = first; j < last; j++)
				if ('a' <= _string[j] && _string[j] <= 'z')
						_string[j] -= ('a' - 'A');
}

void String::downcase(unsigned first, unsigned last) {
		if(first >= last) {
				throw std::exception("First is greater than or equal to last");
		}

		if (last > _length) {
				throw std::exception("Last is greater than length");
		}

		for (unsigned j = first; j < last; j++)
				if ('A' <= _string[j] && _string[j] <= 'Z')
						_string[j] += ('a' - 'A');
}

void String::togglecase(unsigned first, unsigned last) {
		if(first >= last) {
				throw std::exception("First is greater than or equal to last");
		}

		if (last > _length) {
				throw std::exception("Last is greater than length");
		}

		for (unsigned j = first; j < last; j++)
				if ('A' <= _string[j] && _string[j] <= 'Z')
						_string[j] += ('a' - 'A');
				else if ('a' <= _string[j] && _string[j] <= 'z')
						_string[j] -= ('a' - 'A');
}

std::ostream& operator<<(std::ostream& os, const String& s) {
		if (s.len() > 0) {
				for (unsigned j = 0; j < s.len(); j++)
						os << s[j];
		}
		else os << "";

		return os;
}

std::istream& operator>>(std::istream& is, String& s) {
		char* c = new char[1000];
		is >> c;
		s = String(c);
		delete[] c;

		return is;
}

char String::operator[](unsigned j) const {
		if (j >= _length) throw std::exception("Out of range");
		return _string[j];
}

char& String::operator[](unsigned j) {
		if (j >= _length) throw std::exception("Out of range");
		return _string[j];
}

String& String::operator=(const String& s) {
		if (this == &s) return *this;

		delete _string;
		_length = s.len();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
		return *this;
}

String& String::operator+=(const String& s) {
		unsigned len = _length + s.len();
		char* str = new char[len];

		for (unsigned j = 0; j < _length; j++)
				str[j] = _string[j];

		for (unsigned i = 0; i < s.len(); i++)
				str[_length + i] = s[i];

		delete _string;
		_length = len;
		_string = str;
		return *this;
}

String operator+(const String& lhs, const String& rhs) {
		return String(lhs) += rhs;
}

String operator+(const String& lhs, char rhs) {
		return String(lhs) += String(rhs);
}

String operator+(const String& lhs, const char* rhs) {
		return String(lhs) += String(rhs);
}

String operator+(char lhs, const String& rhs) {
		return String(lhs) += rhs;
}

String operator+(const char* lhs, const String& rhs) {
		return String(lhs) += rhs;
}