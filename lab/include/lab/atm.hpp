#ifndef LAB_ATM_HPP
#define LAB_ATM_HPP

#include <iosfwd>
#include <fstream>
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

            friend std::istream& operator>>(std::istream &in, const ATM& atm);

            friend std::ostream& operator<<(std::ostream &out, const ATM& atm);

            friend std::ifstream& operator>>(std::ifstream &in, const ATM& atm);

            friend std::ofstream& operator<<(std::ofstream &out, const ATM& atm);

            static lab::ATM from_binary(std::ifstream &in);

            std::ofstream& to_binary(std::ofstream &out);

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

    std::istream& operator>>(std::istream &in, const ATM& atm);

    std::ostream& operator<<(std::ostream &out, const ATM& atm);

    std::ifstream& operator>>(std::ifstream &in, const ATM& atm);

    std::ofstream& operator<<(std::ofstream &out, const ATM& atm);
}

#endif //LAB_ATM_HPP