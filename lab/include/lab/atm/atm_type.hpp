#ifndef ATM_TYPE_H
#define ATM_TYPE_H
#include <iostream>
#include <type_traits>

namespace lab {
    enum class ATM_type {
            Base,
            Fields,
            Reports
    };

    inline std::istream& operator>>(std::istream& in, lab::ATM_type& type) {
        std::underlying_type_t<lab::ATM_type> number;
        in >> number;

        switch (static_cast<lab::ATM_type>(number)) {
        case lab::ATM_type::Base:
            type = lab::ATM_type::Base;
            break;
        case lab::ATM_type::Fields:
            type = lab::ATM_type::Fields;
            break;
        case lab::ATM_type::Reports:
            type = lab::ATM_type::Reports;
            break;
        }

        return in;
    }

    inline std::ostream& operator<<(std::ostream& out, const lab::ATM_type& type) {
        out << static_cast<int>(type);

        return out;
    }
}
#endif //ATM_TYPE_H