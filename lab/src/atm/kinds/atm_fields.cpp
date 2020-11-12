#include <lab/atm/kinds/atm_fields.hpp>
#include <iostream>

lab::ATM_fields::ATM_fields(const lab::ATM_fields& atm)
        :ATM(atm) {
    m_bankname = new common::string(*atm.m_bankname);
    m_location = new common::string(*atm.m_location);
}

lab::ATM_fields::ATM_fields(const common::string& id,
        const common::string& bankname,
        const common::string& location,
        float max_withdraw,
        float initial_balance)
        :ATM(id, max_withdraw, initial_balance) {
    m_bankname = new common::string(bankname);
    m_location = new common::string(location);
}

lab::ATM_fields& lab::ATM_fields::operator=(const lab::ATM_fields& other) {
    if (this != &other) {
        delete m_bankname;
        delete m_location;

        m_bankname = new common::string(*other.m_bankname);
        m_location = new common::string(*other.m_location);
    }

    this->lab::ATM::operator=(other);

    return *this;
}

const char* lab::ATM_fields::bankname() {
    return this->m_bankname->c_str();
}

const char* lab::ATM_fields::location() {
    return this->m_location->c_str();
}

void lab::ATM_fields::write(std::ostream& out) {
    out <<
        "< ATM with Fields >" << std::endl <<
        "ID: " << *this->m_id << std::endl <<
        "Bank name: " << *this->m_bankname << std::endl <<
        "Location: " << *this->m_location << std::endl <<
        "Balance: " << *this->m_balance << std::endl <<
        "Max withdraw: " << *this->m_max_withdraw << std::endl;
}

void lab::ATM_fields::read(std::istream& in) {
    std::cout << "Input ID:" << std::endl;
    in >> *this->m_id;

    std::cout << "Input bank name:" << std::endl;
    in >> *this->m_bankname;

    std::cout << "Input location:" << std::endl;
    in >> *this->m_location;

    std::cout << "Input initial balance:" << std::endl;
    in >> *this->m_balance;

    std::cout << "Input max withdraw sum:" << std::endl;
    in >> *this->m_max_withdraw;
}
