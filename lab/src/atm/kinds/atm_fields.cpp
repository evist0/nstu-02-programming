#include <lab/atm/kinds/atm_fields.hpp>
#include <iostream>
#include <cstring>

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
        "ID: " << this->id() << std::endl <<
        "Bank name: " << this->bankname() << std::endl <<
        "Location: " << this->location() << std::endl <<
        "Balance: " << this->balance() << std::endl <<
        "Max withdraw: " << this->max_withdraw() << std::endl;
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

lab::ATM* lab::ATM_fields::load_text(std::ifstream& in) {
    common::string id;
    common::string bankname;
    common::string location;
    float max_withdraw;
    float balance;

    in >> id;
    in >> bankname;
    in >> location;
    in >> max_withdraw;
    in >> balance;

    return new ATM_fields(id, bankname, location, max_withdraw, balance);
}

void lab::ATM_fields::save_text(std::ofstream& out) {
    out << this->id() << ' ';
    out << this->bankname() << ' ';
    out << this->location() << ' ';
    out << this->max_withdraw() << ' ';
    out << this->balance();

    out << std::endl;
}

lab::ATM* lab::ATM_fields::load_bin(std::ifstream& in) {
    size_t id_length = 0;
    size_t bankname_length = 0;
    size_t location_length = 0;
    float balance;
    float max_withdraw;

    in.read(reinterpret_cast<char*>(&id_length), sizeof(size_t));
    char* id = new char[id_length + 1];
    in.read(id, id_length);
    id[id_length] = '\0';

    in.read(reinterpret_cast<char*>(&bankname_length), sizeof(size_t));
    char* bankname = new char[bankname_length + 1];
    in.read(bankname, bankname_length);
    bankname[bankname_length] = '\0';

    in.read(reinterpret_cast<char*>(&location_length), sizeof(size_t));
    char* location = new char[location_length + 1];
    in.read(location, location_length);
    location[location_length] = '\0';

    in.read(reinterpret_cast<char*>(&max_withdraw), sizeof(float));
    in.read(reinterpret_cast<char*>(&balance), sizeof(float));

    return new ATM_fields(id, bankname, location, max_withdraw, balance);
}

void lab::ATM_fields::save_bin(std::ofstream& out) {
    size_t id_length = strlen(this->id());
    size_t bankname_length = strlen(this->bankname());
    size_t location_length = strlen(this->location());

    float max_withdraw = this->max_withdraw();
    float balance = this->balance();

    out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
    out.write(this->id(), id_length);

    out.write(reinterpret_cast<const char*>(&bankname_length), sizeof(size_t));
    out.write(this->bankname(), bankname_length);

    out.write(reinterpret_cast<const char*>(&location_length), sizeof(size_t));
    out.write(this->location(), location_length);

    out.write(reinterpret_cast<const char*>(&max_withdraw), sizeof(float));
    out.write(reinterpret_cast<const char*>(&balance), sizeof(float));
}
