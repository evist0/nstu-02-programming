#include <sstream>
#include <lab/atm/kinds/atm_reports.hpp>
#include <iostream>
#include <lab/atm/atm_type.hpp>
#include <cstring>

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

lab::ATM* lab::ATM_reports::load_text(std::ifstream& in) {
    common::string id;
    float max_withdraw;
    float balance;
    size_t reports_amount;

    in >> id;
    in >> max_withdraw;
    in >> balance;
    in >> reports_amount;

    auto atm = new ATM_reports(id, max_withdraw, balance, true);

    for (size_t i = 0; i < reports_amount; i++) {
        auto report = lab::Report::from_text(in);

        atm->reports.push_back(report);
    }

    return atm;
}

void lab::ATM_reports::save_text(std::ofstream& out) {
    out << this->id() << ' ';
    out << this->max_withdraw() << ' ';
    out << this->balance() << ' ';
    out << this->reports_amount() << std::endl;

    for (size_t i = 0; i < this->reports_amount(); i++) {
        out << ' ';
        out << this->reports[i] << std::endl;
    }
}

lab::ATM* lab::ATM_reports::load_bin(std::ifstream& in) {
    size_t id_length = 0;

    float balance;
    float max_withdraw;

    in.read(reinterpret_cast<char*>(&id_length), sizeof(size_t));
    char* id = new char[id_length + 1];
    in.read(id, id_length);
    id[id_length] = '\0';

    in.read(reinterpret_cast<char*>(&max_withdraw), sizeof(float));
    in.read(reinterpret_cast<char*>(&balance), sizeof(float));

    size_t reports_amount;
    in.read(reinterpret_cast<char*>(&reports_amount), sizeof(size_t));

    auto atm = new ATM_reports(id, max_withdraw, balance, true);

    for (size_t i = 0; i < reports_amount; i++) {
        auto report = Report::from_binary(in);
        atm->reports.push_back(report);
    }

    return atm;
}

void lab::ATM_reports::save_bin(std::ofstream& out) {
    size_t id_length = strlen(this->id());
    float max_withdraw = this->max_withdraw();
    float balance = this->balance();
    size_t reports_amount = this->reports_amount();

    out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
    out.write(this->id(), id_length);

    out.write(reinterpret_cast<const char*>(&max_withdraw), sizeof(float));
    out.write(reinterpret_cast<const char*>(&balance), sizeof(float));
    out.write(reinterpret_cast<const char*>(&reports_amount), sizeof(size_t));

    for (size_t i = 0; i < reports_amount; i++) {
        this->reports[i].to_binary(out);
    }
}

