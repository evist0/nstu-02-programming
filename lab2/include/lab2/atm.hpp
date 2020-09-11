#ifndef OOP_LABS_ATM_H
#define OOP_LABS_ATM_H

#include <sstream>
#include <lab1/atm.hpp>

namespace lab2 {
    class ATM : public lab1::ATM {
        public:
            ATM(const lab1::string& id, float maxWithdraw = 0.f, float initialBalance = 0.f)
                    :lab1::ATM(id, maxWithdraw, initialBalance) {
            };

            friend ATM operator-(ATM& atm, float withdrawSum);

            friend ATM operator+(ATM& atm, float depositSum);

            friend bool operator==(ATM& atm, float checkSum);

            friend bool operator!=(ATM& atm, float checkSum);

            std::basic_string<char, std::char_traits<char>, std::allocator<char>> operator()();
    };

    ATM operator-(ATM& atm, float withdrawSum);

    ATM operator+(ATM& atm, float depositSum);

    bool operator==(ATM& atm, float checkSum);

    bool operator!=(ATM& atm, float checkSum);

}

#endif //OOP_LABS_ATM_H
