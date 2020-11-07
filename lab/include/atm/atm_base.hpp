#ifndef LAB_ATM_HPP
#define LAB_ATM_HPP

#include <iosfwd>
#include <fstream>
#include <common/string.hpp>

namespace lab {
    class ATM_Base {
        public:
            ATM_Base() noexcept;
            ATM_Base(const ATM_Base& atm);
            ATM_Base(const common::string& id, float maxWithdraw = 0.f, float initialBalance = 0.f);

            virtual void deposit(float amount);
            virtual void withdraw(float amount);

            ATM_Base& operator=(const lab::ATM_Base& other);

            common::string operator()();

            const char* id() const noexcept;
            float balance() const noexcept;
            float maxWithdraw() const noexcept;

            static size_t atmAmount();

            virtual ~ATM_Base();

        protected:
            static size_t atm_amount;
            common::string* m_id;
            float* m_balance;
            float* m_maxWithdraw;
            common::string to_string();

    };

}

#endif //LAB_ATM_HPP