#ifndef MAIN_STRING_H
#define MAIN_STRING_H

#include <iostream>
#include <cstring>

namespace Utils {
		class String {
				private:
						char* _string;
						unsigned _length;
				public:
						//Constructors
						String();
						explicit String(char c);
						explicit String(const char* c);
						String(const String& s);
						explicit String(const std::string& s);
						~String();

						unsigned len() const;

						int index(char c) const;

						void upcase(unsigned first, unsigned last);
						void downcase(unsigned first, unsigned last);
						void togglecase(unsigned first, unsigned last);

						friend std::ostream& operator<<(std::ostream& so, const String& s);
						friend std::istream& operator>>(std::istream& so, String& s);

						char  operator[] (unsigned j) const;
						char& operator[] (unsigned j);

						String& operator= (const String& s);

						String& operator+= (const String& s);

						friend String operator+ (const String& lhs, const String& rhs);
						friend String operator+ (const String& lhs, char          rhs);
						friend String operator+ (const String& lhs, const char*   rhs);
						friend String operator+ (char          lhs, const String& rhs);
						friend String operator+ (const char*   lhs, const String& rhs);
		};
}

#endif //MAIN_STRING_H
