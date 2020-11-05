#ifndef LAB_ATM_HPP
#define LAB_ATM_HPP

#include <iosfwd>
#include <fstream>
#include <common/string.hpp>

namespace lab {
    class ATM_Base {
        public:
            ATM_Base() noexcept;
            ATM_Base(const lab::ATM_Base& atm);
            ATM_Base(const common::string& id, float maxWithdraw = 0.f, float initialBalance = 0.f);

            void deposit(float amount);
            void withdraw(float amount);

            ATM_Base& operator=(const lab::ATM_Base& other);

            friend ATM_Base operator-(ATM_Base& atm, float withdrawSum);

            friend ATM_Base operator+(ATM_Base& atm, float depositSum);

            friend bool operator==(ATM_Base& atm, float checkSum);

            friend bool operator!=(ATM_Base& atm, float checkSum);

            common::string operator()();

            const char* id() const noexcept;
            float balance() const noexcept;
            float maxWithdraw() const noexcept;

            static size_t atmAmount();

            ~ATM_Base();

        protected:
            static size_t atm_amount;
            common::string* m_id;
            float* m_balance;
            float* m_maxWithdraw;
            common::string to_string();

    };

    ATM_Base operator-(ATM_Base& atm, float withdrawSum);

    ATM_Base operator+(ATM_Base& atm, float depositSum);

    bool operator==(ATM_Base& atm, float checkSum);

    bool operator!=(ATM_Base& atm, float checkSum);

    std::istream& operator>>(std::istream &in, const ATM_Base& atm);

    std::ostream& operator<<(std::ostream &out, const ATM_Base& atm);

    std::ifstream& operator>>(std::ifstream &in, const ATM_Base& atm);

    std::ofstream& operator<<(std::ofstream &out, const ATM_Base& atm);
}

#endif //LAB_ATM_HPP