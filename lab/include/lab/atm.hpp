#ifndef LAB_ATM_HPP
#define LAB_ATM_HPP

#include <iosfwd>
#include <common/string.hpp>

namespace lab {
    class ATM {
        public:
            ATM() noexcept;
            ATM(const lab::ATM& atm);
            ATM(const common::string& id, float maxWithdraw = 0.f, float initialBalance = 0.f);

            void deposit(float amount);
            void withdraw(float amount);

            ATM& operator=(const lab::ATM& other);

            friend ATM operator-(ATM& atm, float withdrawSum);

            friend ATM operator+(ATM& atm, float depositSum);

            friend bool operator==(ATM& atm, float checkSum);

            friend bool operator!=(ATM& atm, float checkSum);

            common::string operator()();

            const char* id() const noexcept;
            float balance() const noexcept;
            float maxWithdraw() const noexcept;

            static size_t get_atm_amount();
            common::string to_string();

            ~ATM();

        private:
            static size_t atm_amount;
            common::string* m_id;
            float* m_balance;
            float* m_maxWithdraw;
    };

    ATM operator-(ATM& atm, float withdrawSum);

    ATM operator+(ATM& atm, float depositSum);

    bool operator==(ATM& atm, float checkSum);

    bool operator!=(ATM& atm, float checkSum);
}

#endif //LAB_ATM_HPP