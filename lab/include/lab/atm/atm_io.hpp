#ifndef ATM_IO_H
#define ATM_IO_H
#include <iosfwd>
#include <lab/atm/kinds/atm.hpp>

namespace lab {
    class ATM;

    class ATM_io {
        public:
            static ATM* load_text(std::ifstream& in);
            static void save_text(std::ofstream& out, ATM* atm);
            static ATM* load_bin(std::ifstream& in);
            static void save_bin(std::ofstream& out, ATM* atm);
    };
}
#endif //ATM_IO_H