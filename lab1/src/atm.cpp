#include <lab1/atm.hpp>
#include <cstdlib>

lab1::ATM::ATM(const common::string& id, float maxWithdraw, float initialBalance)
        :m_id(id), m_balance(initialBalance), m_maxWithdraw(maxWithdraw) {
    if (m_maxWithdraw < 0) {
        throw std::runtime_error("Max withdraw less than 0");
    }
    if (m_balance < 0) {
        throw std::runtime_error("Initial balance less than 0");
    }
}

const char* lab1::ATM::id() const noexcept {
    return m_id.c_str();
}

float lab1::ATM::balance() const noexcept {
    return m_balance;
}

float lab1::ATM::maxWithdraw() const noexcept {
    return m_maxWithdraw;
}

void lab1::ATM::deposit(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative depositing sum");
    }

    m_balance += amount;
}

void lab1::ATM::withdraw(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative withdrawing sum");
    }

    if (amount > m_maxWithdraw) {
        throw std::runtime_error("Withdraw amount greater than max");
    }

    if (m_balance - amount < 0) {
        throw std::runtime_error("Amount to withdraw greater than balance");
    }

    m_balance -= amount;
}

common::string lab1::ATM::to_string() {
    char balance_string[64], maxWithdraw_string[64];

    gcvt(m_balance, 64, balance_string);
    gcvt(m_maxWithdraw, 64, maxWithdraw_string);

    common::string result = "ATM Id: " + m_id + '\n' + "Balance: " + balance_string + "\n" + "Max withdraw: "
            + maxWithdraw_string + "\n";

    return result;
}
