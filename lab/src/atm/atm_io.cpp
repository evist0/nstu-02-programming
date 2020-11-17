#include <cstring>
#include <lab/atm/atm_io.hpp>
#include <lab/atm/atm_type.hpp>
#include <lab/atm/kinds/atm_fields.hpp>
#include <lab/atm/kinds/atm_reports.hpp>

lab::ATM* lab::ATM_io::load_text(std::ifstream& in) {
    ATM_type type = ATM_type::Base;
    in >> type;

    if (in.eof()) {
        return nullptr;
    }

    if (type == ATM_type::Base) {
        common::string id = "";
        float max_withdraw = 0.f;
        float balance = 0.f;

        in >> id;
        in >> max_withdraw;
        in >> balance;

        return new ATM(id, max_withdraw, balance);
    }

    else if (type == ATM_type::Fields) {
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

    else if (type == ATM_type::Reports) {
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
}

std::ofstream& lab::ATM_io::save_text(std::ofstream& out, lab::ATM* atm) {

    if (auto casted = dynamic_cast<ATM_fields*>(atm)) {
        out << ATM_type::Fields << ' ';
        out << casted->id() << ' ';
        out << casted->bankname() << ' ';
        out << casted->location() << ' ';
        out << casted->max_withdraw() << ' ';
        out << casted->balance();

        out << std::endl;
        return out;
    }

    else if (auto casted = dynamic_cast<ATM_reports*>(atm)) {
        out << ATM_type::Reports << ' ';
        out << casted->id() << ' ';
        out << casted->max_withdraw() << ' ';
        out << casted->balance() << ' ';
        out << casted->reports_amount() << std::endl;

        for (size_t i = 0; i < casted->reports_amount(); i++) {
            out << ' ';
            out << casted->reports[i] << std::endl;
        }

        return out;
    }

    else if (auto casted = dynamic_cast<ATM*>(atm)) {
        out << ATM_type::Base << ' ';
        out << casted->id() << ' ';
        out << casted->max_withdraw() << ' ';
        out << casted->balance() << ' ';

        out << std::endl;

        return out;
    }

    else {
        throw std::runtime_error("Неизвестный тип банкомата");
    }
}

lab::ATM* lab::ATM_io::load_bin(std::ifstream& in) {
    ATM_type type;
    in.read(reinterpret_cast<char*>(&type), sizeof(ATM_type));

    if (in.eof()) {
        return nullptr;
    }

    if (type == ATM_type::Base) {
        size_t id_length = 0;

        float balance;
        float max_withdraw;

        in.read(reinterpret_cast<char*>(&id_length), sizeof(size_t));
        char* id = new char[id_length + 1];
        in.read(id, id_length);
        id[id_length] = '\0';

        in.read(reinterpret_cast<char*>(&max_withdraw), sizeof(float));
        in.read(reinterpret_cast<char*>(&balance), sizeof(float));

        return new ATM(id, max_withdraw, balance);
    }

    else if (type == ATM_type::Fields) {
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

    else if (type == ATM_type::Reports) {
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
}

std::ofstream& lab::ATM_io::save_bin(std::ofstream& out, lab::ATM* atm) {

    if (auto casted = dynamic_cast<ATM_fields*>(atm)) {
        ATM_type type = ATM_type::Fields;
        size_t id_length = strlen(casted->id());
        size_t bankname_length = strlen(casted->bankname());
        size_t location_length = strlen(casted->location());

        float max_withdraw = casted->max_withdraw();
        float balance = casted->balance();

        out.write(reinterpret_cast<const char*>(&type), sizeof(ATM_type));

        out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
        out.write(casted->id(), id_length);

        out.write(reinterpret_cast<const char*>(&bankname_length), sizeof(size_t));
        out.write(casted->bankname(), bankname_length);

        out.write(reinterpret_cast<const char*>(&location_length), sizeof(size_t));
        out.write(casted->location(), location_length);

        out.write(reinterpret_cast<const char*>(&max_withdraw), sizeof(float));
        out.write(reinterpret_cast<const char*>(&balance), sizeof(float));

        return out;
    }

    else if (auto casted = dynamic_cast<ATM_reports*>(atm)) {
        ATM_type type = ATM_type::Reports;
        size_t id_length = strlen(casted->id());
        float max_withdraw = casted->max_withdraw();
        float balance = casted->balance();
        size_t reports_amount = casted->reports_amount();

        out.write(reinterpret_cast<const char*>(&type), sizeof(ATM_type));

        out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
        out.write(casted->id(), id_length);

        out.write(reinterpret_cast<const char*>(&max_withdraw), sizeof(float));
        out.write(reinterpret_cast<const char*>(&balance), sizeof(float));
        out.write(reinterpret_cast<const char*>(&reports_amount), sizeof(size_t));

        for (size_t i = 0; i < reports_amount; i++) {
            casted->reports[i].to_binary(out);
        }

        return out;
    }

    else if (auto casted = dynamic_cast<ATM*>(atm)) {
        ATM_type type = ATM_type::Base;
        size_t id_length = strlen(casted->id());
        float max_withdraw = casted->max_withdraw();
        float balance = casted->balance();

        out.write(reinterpret_cast<const char*>(&type), sizeof(ATM_type));

        out.write(reinterpret_cast<const char*>(&id_length), sizeof(size_t));
        out.write(casted->id(), id_length);

        out.write(reinterpret_cast<const char*>(&max_withdraw), sizeof(float));
        out.write(reinterpret_cast<const char*>(&balance), sizeof(float));

        return out;
    }

    else {
        throw std::runtime_error("Неизвестный тип банкомата");
    }
}