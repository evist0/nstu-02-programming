#include <lab/atm/kinds/atm_reports.hpp>
#include <sstream>
#include <iostream>
#include <cstring>

lab::ATM_reports::ATM_reports(const lab::ATM_reports& atm) {
    this->reports = Report_Container();

    lab::Report report = Report(Action::Enabled, std::chrono::system_clock::now(), 0);
    this->reports.push_back(report);
}

lab::ATM_reports::ATM_reports(const common::string& id, float max_withdraw, float initial_balance, bool loaded)
        :ATM(id, max_withdraw, initial_balance) {
    this->reports = Report_Container();


    if (!loaded) {
        lab::Report report = Report(Action::Enabled, std::chrono::system_clock::now(), 0);
        this->reports.push_back(report);
    }
}

lab::ATM_reports& lab::ATM_reports::operator=(const lab::ATM_reports& other) {
    this->lab::ATM::operator=(other);

    return *this;
}

size_t lab::ATM_reports::reports_amount() const {
    return reports.length();
}

common::string lab::ATM_reports::log() {
    std::stringstream ss;

    for (size_t i = 0; i < this->reports_amount(); i++) {
        if (this->reports[i].is_today()) {
            ss << this->reports[i];
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
    lab::Report report = Report(Action::Disabled, std::chrono::system_clock::now(), 0);
    this->reports.push_back(report);
}

void lab::ATM_reports::deposit(float amount) {
    ATM::deposit(amount);

    lab::Report report = Report(Action::Deposit, std::chrono::system_clock::now(), amount);
    this->reports.push_back(report);
}

void lab::ATM_reports::withdraw(float amount) {
    ATM::withdraw(amount);

    lab::Report report = Report(Action::Withdraw, std::chrono::system_clock::now(), amount);
    this->reports.push_back(report);
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

