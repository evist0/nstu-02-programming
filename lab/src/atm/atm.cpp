#include <iostream>
#include <fstream>
#include <atm/atm.hpp>

common::string lab::ATM::bankName() {
    return this->m_bankName;
}

common::string lab::ATM::location() {
    return this->m_location;
}

lab::ATM::ATM()
        :ATM_Base(), ATM_Report() {
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

std::istream& lab::operator>>(std::istream& in, const lab::ATM& atm) {
    std::cout << "Input ID:" << std::endl;
    in >> *atm.m_id;

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
        std::endl;

    return out;
}

std::ifstream& lab::operator>>(std::ifstream& in, const lab::ATM& atm) {
    in >> static_cast<common::string>(*atm.m_id) >> *atm.m_balance >> *atm.m_maxWithdraw;

    return in;
}

std::ofstream& lab::operator<<(std::ofstream& out, const lab::ATM& atm) {
    out << atm.id() << " " << atm.balance() << " " << atm.maxWithdraw() << std::endl;

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

    return ATM(bank, location, id, maxWithdraw,balance);
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
