#ifndef COMMON_STRING_HPP
#define COMMON_STRING_HPP

#include <iosfwd>
#include <string>
#include <sstream>

namespace common {
		class string {
				public:
						string();
						explicit string(char c);
						string(const char* c);
						string(const string& s);
						explicit string(const std::string& s);
						~string();

						unsigned len() const;

						int index(char c) const;

						void upcase(unsigned first, unsigned last);
						void downcase(unsigned first, unsigned last);
						void togglecase(unsigned first, unsigned last);

						friend std::ostream& operator<<(std::ostream& os, const string& s);
						friend std::istream& operator>>(std::istream& is, string& s);

						char operator[](unsigned j) const;
						char& operator[](unsigned j);

						const char* c_str() const noexcept;

						string& operator=(const string& s);

						string& operator+=(const string& s);

						friend string operator+(const string& lhs, const string& rhs);
						friend string operator+(const string& lhs, char rhs);
						friend string operator+(const string& lhs, const char* rhs);
						friend string operator+(char lhs, const string& rhs);
						friend string operator+(const char* lhs, const string& rhs);

						friend bool operator==(const string& lhs, const string& rhs);
						friend bool operator==(const string& lhs, char rhs);
						friend bool operator==(const string& lhs, const char* rhs);
						friend bool operator==(char lhs, const string& rhs);
						friend bool operator==(const char* lhs, const string& rhs);

						friend bool operator!=(const string& lhs, const string& rhs);
						friend bool operator!=(const string& lhs, char rhs);
						friend bool operator!=(const string& lhs, const char* rhs);
						friend bool operator!=(char lhs, const string& rhs);
						friend bool operator!=(const char* lhs, const string& rhs);

						friend bool operator>(const string& lhs, const string& rhs);
						friend bool operator>(const string& lhs, char rhs);
						friend bool operator>(const string& lhs, const char* rhs);
						friend bool operator>(char lhs, const string& rhs);
						friend bool operator>(const char* lhs, const string& rhs);

						friend bool operator>=(const string& lhs, const string& rhs);
						friend bool operator>=(const string& lhs, char rhs);
						friend bool operator>=(const string& lhs, const char* rhs);
						friend bool operator>=(char lhs, const string& rhs);
						friend bool operator>=(const char* lhs, const string& rhs);

						friend bool operator<(const string& lhs, const string& rhs);
						friend bool operator<(const string& lhs, char rhs);
						friend bool operator<(const string& lhs, const char* rhs);
						friend bool operator<(char lhs, const string& rhs);
						friend bool operator<(const char* lhs, const string& rhs);

						friend bool operator<=(const string& lhs, const string& rhs);
						friend bool operator<=(const string& lhs, char rhs);
						friend bool operator<=(const string& lhs, const char* rhs);
						friend bool operator<=(char lhs, const string& rhs);
						friend bool operator<=(const char* lhs, const string& rhs);

				private:
						char* m_string;
						unsigned m_length;
		};

		std::ostream& operator<<(std::ostream& so, const string& s);
		std::istream& operator>>(std::istream& so, string& s);

		string operator+(const string& lhs, const string& rhs);
		string operator+(const string& lhs, char rhs);
		string operator+(const string& lhs, const char* rhs);
		string operator+(char lhs, const string& rhs);
		string operator+(const char* lhs, const string& rhs);

		bool operator==(const string& lhs, const string& rhs);
		bool operator==(const string& lhs, char rhs);
		bool operator==(const string& lhs, const char* rhs);
		bool operator==(char lhs, const string& rhs);
		bool operator==(const char* lhs, const string& rhs);

		bool operator!=(const string& lhs, const string& rhs);
		bool operator!=(const string& lhs, char rhs);
		bool operator!=(const string& lhs, const char* rhs);
		bool operator!=(char lhs, const string& rhs);
		bool operator!=(const char* lhs, const string& rhs);

		bool operator>(const string& lhs, const string& rhs);
		bool operator>(const string& lhs, char rhs);
		bool operator>(const string& lhs, const char* rhs);
		bool operator>(char lhs, const string& rhs);
		bool operator>(const char* lhs, const string& rhs);

		bool operator>=(const string& lhs, const string& rhs);
		bool operator>=(const string& lhs, char rhs);
		bool operator>=(const string& lhs, const char* rhs);
		bool operator>=(char lhs, const string& rhs);
		bool operator>=(const char* lhs, const string& rhs);

		bool operator<(const string& lhs, const string& rhs);
		bool operator<(const string& lhs, char rhs);
		bool operator<(const string& lhs, const char* rhs);
		bool operator<(char lhs, const string& rhs);
		bool operator<(const char* lhs, const string& rhs);

		bool operator<=(const string& lhs, const string& rhs);
		bool operator<=(const string& lhs, char rhs);
		bool operator<=(const string& lhs, const char* rhs);
		bool operator<=(char lhs, const string& rhs);
		bool operator<=(const char* lhs, const string& rhs);
}

#endif //COMMON_STRING_HPP