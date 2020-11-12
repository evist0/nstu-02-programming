#ifndef ATM_IO_H
#define ATM_IO_H
#include <lab/atm/kinds/atm.hpp>
#include <fstream>

namespace lab {
    class ATM_io {
        public:
            static ATM* load_text(std::ifstream& in);
            static std::ofstream& save_text(std::ofstream& out, ATM* atm);
            static ATM* load_bin(std::ifstream& in);
            static std::ofstream& save_bin(std::ofstream& out, ATM* atm);
    };
}
#endif //ATM_IO_H