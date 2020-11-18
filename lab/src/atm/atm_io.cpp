#include <cstring>
#include <lab/atm/atm_io.hpp>
#include <lab/atm/atm_type.hpp>
#include <lab/atm/kinds/atm_fields.hpp>
#include <lab/atm/kinds/atm_reports.hpp>

lab::ATM* lab::ATM_io::load_text(std::ifstream& in) {
    ATM_type type = ATM_type::Base;
    in >> type;

    if (type == ATM_type::Base) {
        return lab::ATM::load_text(in);
    }

    else if (type == ATM_type::Fields) {
        return lab::ATM_fields::load_text(in);
    }

    else if (type == ATM_type::Reports) {
        return lab::ATM_reports::load_text(in);
    }

    else {
        return nullptr;
    }
}

void lab::ATM_io::save_text(std::ofstream& out, lab::ATM* atm) {

    if (dynamic_cast<ATM_fields*>(atm)) {
        out << ATM_type::Fields << ' ';
    }

    else if (dynamic_cast<ATM_reports*>(atm)) {
        out << ATM_type::Reports << ' ';
    }

    else if (dynamic_cast<ATM*>(atm)) {
        out << ATM_type::Base << ' ';
    }

    else {
        throw std::runtime_error("Неизвестный тип банкомата");
    }

    atm->save_text(out);
}

lab::ATM* lab::ATM_io::load_bin(std::ifstream& in) {
    ATM_type type;
    in.read(reinterpret_cast<char*>(&type), sizeof(ATM_type));

    if (type == ATM_type::Base) {
        return lab::ATM::load_bin(in);
    }

    else if (type == ATM_type::Fields) {
        return lab::ATM_fields::load_bin(in);
    }

    else if (type == ATM_type::Reports) {
        return lab::ATM_reports::load_bin(in);
    }

    else {
        return nullptr;
    }
}

void lab::ATM_io::save_bin(std::ofstream& out, lab::ATM* atm) {
    ATM_type type;

    if (dynamic_cast<ATM_fields*>(atm)) {
        type = lab::ATM_type::Fields;
    }

    else if (dynamic_cast<ATM_reports*>(atm)) {
        type = lab::ATM_type::Reports;
    }

    else if (dynamic_cast<ATM*>(atm)) {
        type = lab::ATM_type::Base;
    }

    else {
        throw std::runtime_error("Неизвестный тип банкомата");
    }

    out.write(reinterpret_cast<const char*>(&type), sizeof(ATM_type));
    atm->save_bin(out);
}