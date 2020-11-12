#ifndef ATM_H
#define ATM_H
#include <iosfwd>
#include <fstream>
#include <common/string.hpp>

namespace lab {
    class ATM {
        public:
            ATM(const lab::ATM& atm);
            ATM(const common::string& id = "not_provided", float max_withdraw = 0.f, float initial_balance = 0.f);
            ATM& operator=(const lab::ATM& other);

            const char* id() const noexcept;
            float balance() const noexcept;
            float max_withdraw() const noexcept;

            void deposit(float amount);
            void withdraw(float amount);

            friend ATM operator-(ATM& atm, float withdraw_sum);
            friend ATM operator+(ATM& atm, float deposit_sum);
            friend bool operator==(ATM& atm, float check_sum);
            friend bool operator!=(ATM& atm, float check_sum);

            friend std::istream& operator>>(std::istream& in, ATM& atm);
            friend std::ostream& operator<<(std::ostream& out, ATM& atm);

            virtual ~ATM();
        protected:
            static size_t atm_amount;
            common::string* m_id;
            float* m_max_withdraw;
            float* m_balance;
        private:
            virtual void write(std::ostream& out);
            virtual void read(std::istream& in);
    };

    std::istream& operator>>(std::istream& in, ATM& atm);
    std::ostream& operator<<(std::ostream& out, ATM& atm);
    ATM operator+(ATM& atm, float deposit_sum);
    ATM operator-(ATM& atm, float withdraw_sum);
}
#endif //ATM_H