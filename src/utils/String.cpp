#include <String.h>

Utils::String::String() {
		_length = 0;
		_string = new char[0];
}

Utils::String::String(char c) {
		_length = 0;
		_string = new char(c);
}

Utils::String::String(const char* c) {
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

Utils::String::String(const String& s) {
		_length = s.len();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
}

Utils::String::String(const std::string& s) {
		_length = s.length();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
}

Utils::String::~String() {
		delete[] _string;
}

unsigned Utils::String::len() const {
		return _length;
}

int Utils::String::index(char c) const {
		for (unsigned j = 0; j < _length; j++)
				if (_string[j] == c) return (int)j;
		return -1;
}

void Utils::String::upcase(unsigned first, unsigned last) {
		if (first >= last) {
				throw std::exception();
		}

		if (last > _length) {
				throw std::exception();
		}

		for (unsigned j = first; j < last; j++)
				if ('a' <= _string[j] && _string[j] <= 'z')
						_string[j] -= ('a' - 'A');
}

void Utils::String::downcase(unsigned first, unsigned last) {
		if (first >= last) {
				throw std::exception();
		}

		if (last > _length) {
				throw std::exception();
		}

		for (unsigned j = first; j < last; j++)
				if ('A' <= _string[j] && _string[j] <= 'Z')
						_string[j] += ('a' - 'A');
}

void Utils::String::togglecase(unsigned first, unsigned last) {
		if (first >= last) {
				throw std::exception();
		}

		if (last > _length) {
				throw std::exception();
		}

		for (unsigned j = first; j < last; j++)
				if ('A' <= _string[j] && _string[j] <= 'Z')
						_string[j] += ('a' - 'A');
				else if ('a' <= _string[j] && _string[j] <= 'z')
						_string[j] -= ('a' - 'A');
}

std::ostream& Utils::operator<<(std::ostream& os, const Utils::String& s) {
		if (s.len() > 0) {
				for (unsigned j = 0; j < s.len(); j++)
						os << s[j];
		}
		else os << "";

		return os;
}

std::istream& Utils::operator>>(std::istream& is, Utils::String& s) {
		char* c = new char[1000];
		is >> c;
		s = Utils::String(c);
		delete[] c;

		return is;
}

char Utils::String::operator[](unsigned j) const {
		if (j >= _length) throw std::exception();
		return _string[j];
}

char& Utils::String::operator[](unsigned j) {
		if (j >= _length) throw std::exception();
		return _string[j];
}

Utils::String& Utils::String::operator=(const String& s) {
		if (this == &s) return *this;

		delete[] _string;
		_length = s.len();
		_string = new char[_length];
		for (unsigned j = 0; j < _length; j++)
				_string[j] = s[j];
		return *this;
}

Utils::String& Utils::String::operator+=(const String& s) {
		unsigned len = _length + s.len();
		char* str = new char[len];

		for (unsigned j = 0; j < _length; j++)
				str[j] = _string[j];

		for (unsigned i = 0; i < s.len(); i++)
				str[_length + i] = s[i];

		delete[] _string;
		_length = len;
		_string = str;
		return *this;
}

Utils::String Utils::operator+(const Utils::String& lhs, const Utils::String& rhs) {
		return Utils::String(lhs) += Utils::String(rhs);
}

Utils::String Utils::operator+(const Utils::String& lhs, char rhs) {
		return Utils::String(lhs) += Utils::String(rhs);
}

Utils::String Utils::operator+(const Utils::String& lhs, const char* rhs) {
		return Utils::String(lhs) += Utils::String(rhs);
}

Utils::String Utils::operator+(char lhs, const Utils::String& rhs) {
		return Utils::String(lhs) += rhs;
}

Utils::String Utils::operator+(const char* lhs, const Utils::String& rhs) {
		return Utils::String(lhs) += rhs;
}