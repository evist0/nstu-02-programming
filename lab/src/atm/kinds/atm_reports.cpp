#include <sstream>
#include <lab/atm/kinds/atm_reports.hpp>
#include <iostream>

lab::ATM_reports::ATM_reports(const lab::ATM_reports& atm) {
    this->reports = std::vector<Report>();
    this->reports.emplace_back(Action::Enabled, std::chrono::system_clock::now(), 0);
}

lab::ATM_reports::ATM_reports(const common::string& id, float max_withdraw, float initial_balance, bool loaded)
        :ATM(id, max_withdraw, initial_balance) {
    this->reports = std::vector<Report>();

    if (!loaded) {
        this->reports.emplace_back(Action::Enabled, std::chrono::system_clock::now(), 0);
    }
}

lab::ATM_reports& lab::ATM_reports::operator=(const lab::ATM_reports& other) {
    this->lab::ATM::operator=(other);

    return *this;
}

size_t lab::ATM_reports::reports_amount() const {
    return reports.size();
}

common::string lab::ATM_reports::log() {
    std::stringstream ss;
    auto iterator = this->reports.begin();

    for (; iterator != this->reports.end(); iterator++) {
        if (iterator->is_today()) {
            ss << *iterator;
        }
    }

    return common::string(ss.str());
}

void lab::ATM_reports::write(std::ostream& out) {
    out <<
        "< ATM with Reports >" << std::endl <<
        "ID: " << this->id() << std::endl <<
        "Balance: " << this->balance() << std::endl <<
        "Max withdraw: " << this->max_withdraw() << std::endl <<
        "Reports amount: " << this->reports_amount() << std::endl;
}

void lab::ATM_reports::read(std::istream& in) {
    std::cout << "Input ID:" << std::endl;
    in >> *this->m_id;

    std::cout << "Input initial balance:" << std::endl;
    in >> *this->m_balance;

    std::cout << "Input max withdraw sum:" << std::endl;
    in >> *this->m_max_withdraw;
}

lab::ATM_reports::~ATM_reports() {
    this->reports.emplace_back(Action::Disabled, std::chrono::system_clock::now(), 0);
}

void lab::ATM_reports::deposit(float amount) {
    ATM::deposit(amount);
    this->reports.emplace_back(Action::Deposit, std::chrono::system_clock::now(), amount);
}

void lab::ATM_reports::withdraw(float amount) {
    ATM::withdraw(amount);
    this->reports.emplace_back(Action::Withdraw, std::chrono::system_clock::now(), amount);
}

