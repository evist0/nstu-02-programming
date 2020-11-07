#include <iostream>
#include <fstream>
#include <atm/atm.hpp>

common::string lab::ATM::bankName() const noexcept {
    return this->m_bankName;
}

common::string lab::ATM::location() const noexcept {
    return this->m_location;
}

lab::ATM::ATM()
        :ATM_Base(), ATM_Report() {
    this->m_bankName = "not_provided";
    this->m_location = "not_provided";
}

lab::ATM::ATM(const common::string& bankName,
        const common::string& location,
        const common::string& id,
        float maxWithdraw,
        float initialBalance)
        :ATM_Base(id, maxWithdraw, initialBalance), ATM_Report() {
    this->m_bankName = bankName;
    this->m_location = location;
}

lab::ATM::ATM(const lab::ATM& atm)
        :ATM_Base(atm), ATM_Report(atm) {
    this->m_location = common::string(atm.m_location);
    this->m_bankName = common::string(atm.m_bankName);
}

std::istream& lab::operator>>(std::istream& in, lab::ATM& atm) {
    std::cout << "Input ID:" << std::endl;
    in >> *atm.m_id;

    std::cout << "Input bank name:" << std::endl;
    in >> atm.m_bankName;

    std::cout << "Input ATM location:" << std::endl;
    in >> atm.m_location;

    std::cout << "Input initial balance:" << std::endl;
    in >> *atm.m_balance;

    std::cout << "Input max withdraw sum:" << std::endl;
    in >> *atm.m_maxWithdraw;

    return in;
}

std::ostream& lab::operator<<(std::ostream& out, const lab::ATM& atm) {
    out <<
        "<- ATM_Base ->" << std::endl <<
        "ID: " << atm.id() << std::endl <<
        "Balance: " << atm.balance() << std::endl <<
        "Max withdraw: " << atm.maxWithdraw() << std::endl <<
        "Bank: " << atm.bankName() << std::endl <<
        "Location: " << atm.location() << std::endl <<
        std::endl;

    return out;
}

std::ifstream& lab::operator>>(std::ifstream& in, ATM& atm) {
    in >>
       *atm.m_id >>
       atm.m_bankName >>
       atm.m_location >>
       *atm.m_balance >>
       *atm.m_maxWithdraw;

    return in;
}

std::ofstream& lab::operator<<(std::ofstream& out, const lab::ATM& atm) {
    out <<
        atm.id() << " " <<
        atm.bankName() << " " <<
        atm.location() << " " <<
        atm.balance() << " " <<
        atm.maxWithdraw() << " " <<
        std::endl;

    return out;
}

lab::ATM lab::ATM::from_binary(std::ifstream& in) {
    size_t id_length = 0;
    size_t bank_length = 0;
    size_t location_length = 0;
    float balance;
    float maxWithdraw;

    in.read(reinterpret_cast<char*>(&id_length), sizeof(size_t));
    char* id = new char[id_length + 1];
    in.read(id, id_length);
    id[id_length] = '\0';

    in.read(reinterpret_cast<char*>(&bank_length), sizeof(size_t));
    char* bank = new char[bank_length + 1];
    in.read(bank, bank_length);
    id[bank_length] = '\0';

    in.read(reinterpret_cast<char*>(&location_length), sizeof(size_t));
    char* location = new char[location_length + 1];
    in.read(location, location_length);
    id[location_length] = '\0';

    in.read(reinterpret_cast<char*>(&balance), sizeof(float));
    in.read(reinterpret_cast<char*>(&maxWithdraw), sizeof(float));

    return ATM(bank, location, id, maxWithdraw, balance);
}

std::ofstream& lab::ATM::to_binary(std::ofstream& out) {
    size_t id_length = this->m_id->len();
    size_t bank_length = this->m_bankName.len();
    size_t location_length = this->m_location.len();

    out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
    out.write(this->m_id->c_str(), id_length);

    out.write(reinterpret_cast<const char*>(&bank_length), sizeof(size_t));
    out.write(this->m_bankName.c_str(), bank_length);

    out.write(reinterpret_cast<const char*>(&location_length), sizeof(size_t));
    out.write(this->m_location.c_str(), location_length);

    out.write(reinterpret_cast<const char*>(this->m_balance), sizeof(float));
    out.write(reinterpret_cast<const char*>(this->m_maxWithdraw), sizeof(float));

    return out;
}

lab::ATM& lab::ATM::operator=(const lab::ATM& atm) {
    if (this != &atm) {
        delete m_id;

        m_id = new common::string(*atm.m_id);
        m_bankName = common::string(atm.m_bankName);
        m_location = common::string(atm.m_location);
        *m_balance = *atm.m_balance;
        *m_maxWithdraw = *atm.m_maxWithdraw;
    }

    return *this;
}

lab::ATM lab::operator-(lab::ATM& atm, float withdrawSum) {
    atm.withdraw(withdrawSum);

    return atm;
}

lab::ATM lab::operator+(lab::ATM& atm, float depositSum) {
    atm.deposit(depositSum);

    return atm;
}

void lab::ATM::deposit(float amount) {
    ATM_Base::deposit(amount);
    this->reports.emplace_back(Report_Action::Deposit, amount);
}

void lab::ATM::withdraw(float amount) {
    ATM_Base::withdraw(amount);
    this->reports.emplace_back(Report_Action::Withdraw, amount);
}

bool lab::operator==(lab::ATM& atm, float checkSum) {
    return atm.balance() == checkSum;
}

bool lab::operator!=(lab::ATM& atm, float checkSum) {
    return atm.balance() != checkSum;
}
