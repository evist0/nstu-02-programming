#include <lab/atm.hpp>
#include <cstdlib>
#include <iostream>

size_t lab::ATM::atm_amount = 0;

lab::ATM::ATM() noexcept {
    m_id = new common::string("not_provided");
    m_maxWithdraw = new float(0.f);
    m_balance = new float(0.f);

    atm_amount++;
}

lab::ATM::ATM(const lab::ATM& atm) {
    m_id = new common::string(*atm.m_id);
    m_balance = new float(*atm.m_balance);
    m_maxWithdraw = new float(*atm.m_maxWithdraw);

    atm_amount++;
}

lab::ATM::ATM(const common::string& id, float maxWithdraw, float initialBalance) {
    if (maxWithdraw < 0) {
        throw std::runtime_error("Max withdraw less than 0");
    }
    if (initialBalance < 0) {
        throw std::runtime_error("Initial balance less than 0");
    }

    m_id = new common::string(id);
    m_maxWithdraw = new float(maxWithdraw);
    m_balance = new float(initialBalance);

    atm_amount++;
}

const char* lab::ATM::id() const noexcept {
    return m_id->c_str();
}

float lab::ATM::balance() const noexcept {
    return *m_balance;
}

float lab::ATM::maxWithdraw() const noexcept {
    return *m_maxWithdraw;
}

void lab::ATM::deposit(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative depositing sum");
    }

    *m_balance += amount;
}

void lab::ATM::withdraw(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Negative withdrawing sum");
    }

    if (amount > *m_maxWithdraw) {
        throw std::runtime_error("Withdraw amount greater than max");
    }

    if (*m_balance - amount < 0) {
        throw std::runtime_error("Amount to withdraw greater than balance");
    }

    *m_balance -= amount;
}

size_t lab::ATM::get_atm_amount() {
    return atm_amount;
}

common::string lab::ATM::to_string() {
    char balance_string[64], maxWithdraw_string[64];

    gcvt(*m_balance, 64, balance_string);
    gcvt(*m_maxWithdraw, 64, maxWithdraw_string);

    common::string result =
            common::string("<==== ATM INFORMATION ====> \n") +
                    common::string("ATM Id: ") + *m_id + '\n' +
                    common::string("Balance: ") + balance_string + "\n" +
                    common::string("Max withdraw: ") + maxWithdraw_string + "\n\n";

    return result;
}

lab::ATM::~ATM() {
    delete m_id;
    delete m_maxWithdraw;
    delete m_balance;

    atm_amount--;
}

lab::ATM lab::operator-(lab::ATM& atm, float withdrawSum) {
    atm.withdraw(withdrawSum);
    return atm;
}

lab::ATM lab::operator+(lab::ATM& atm, float depositSum) {
    atm.deposit(depositSum);
    return atm;
}

bool lab::operator==(lab::ATM& atm, float checkSum) {
    return atm.balance() == checkSum;
}

bool lab::operator!=(lab::ATM& atm, float checkSum) {
    return atm.balance() != checkSum;
}

common::string lab::ATM::operator()() {
    return this->to_string();
}

lab::ATM& lab::ATM::operator=(const lab::ATM& atm) {
    if(this != &atm) {
        delete m_id;
        delete m_maxWithdraw;
        delete m_balance;

        m_id = new common::string(*atm.m_id);
        m_balance = new float(*atm.m_balance);
        m_maxWithdraw = new float(*atm.m_maxWithdraw);
    }

    return *this;
}
