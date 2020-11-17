#include <lab/atm/kinds/atm.hpp>
#include <iostream>

size_t lab::ATM::atm_amount = 0;

lab::ATM::ATM(const ATM& atm) {
    m_id = new common::string(*atm.m_id);
    m_balance = new float(*atm.m_balance);
    m_max_withdraw = new float(*atm.m_max_withdraw);

    ++atm_amount;
}

lab::ATM::ATM(const common::string& id, float max_withdraw, float initial_balance) {
    if (max_withdraw < 0) {
        throw std::runtime_error("Максимальная сумма снятия меньше 0");
    }
    if (initial_balance < 0) {
        throw std::runtime_error("Начальный баланс меньше 0");
    }

    m_id = new common::string(id);
    m_max_withdraw = new float(max_withdraw);
    m_balance = new float(initial_balance);

    ++atm_amount;
}

lab::ATM& lab::ATM::operator=(const ATM& other) {
    if (this != &other) {
        delete m_id;

        m_id = new common::string(*other.m_id);
        *m_balance = *other.m_balance;
        *m_max_withdraw = *other.m_max_withdraw;
    }

    return *this;
}

const char* lab::ATM::id() const noexcept {
    return m_id->c_str();
}

float lab::ATM::balance() const noexcept {
    return *m_balance;
}

float lab::ATM::max_withdraw() const noexcept {
    return *m_max_withdraw;
}

void lab::ATM::deposit(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Отрицательная сумма депозита");
    }

    *m_balance += amount;
}

void lab::ATM::withdraw(float amount) {
    if (amount < 0) {
        throw std::runtime_error("Отрицательная сумма вывода");
    }

    if (amount > *m_max_withdraw) {
        throw std::runtime_error("Сумма вывода больше допустимой");
    }

    if (*m_balance - amount < 0) {
        throw std::runtime_error("Сумма вывода больше баланса");
    }

    *m_balance -= amount;
}

lab::ATM lab::operator-(lab::ATM& atm, float withdraw_sum) {
    atm.withdraw(withdraw_sum);
    return atm;
}

lab::ATM lab::operator+(lab::ATM& atm, float deposit_sum) {
    atm.deposit(deposit_sum);
    return atm;
}

bool operator==(lab::ATM& atm, float check_sum) {
    return atm.balance() == check_sum;
}

bool operator!=(lab::ATM& atm, float check_sum) {
    return atm.balance() != check_sum;
}

lab::ATM::~ATM() {
    delete m_id;
    delete m_max_withdraw;
    delete m_balance;

    --atm_amount;
}

void lab::ATM::write(std::ostream& out) {
    out <<
        "< ATM Base >" << std::endl <<
        "ID: " << this->id() << std::endl <<
        "Balance: " << this->balance() << std::endl <<
        "Max withdraw: " << this->max_withdraw() << std::endl;
}

void lab::ATM::read(std::istream& in) {
    std::cout << "Input ID:" << std::endl;
    in >> *this->m_id;

    std::cout << "Input initial balance:" << std::endl;
    in >> *this->m_balance;

    std::cout << "Input max withdraw sum:" << std::endl;
    in >> *this->m_max_withdraw;
}

std::istream& lab::operator>>(std::istream& in, lab::ATM& atm) {
    atm.read(in);

    return in;
}

std::ostream& lab::operator<<(std::ostream& out, lab::ATM& atm) {
    atm.write(out);

    return out;
}
