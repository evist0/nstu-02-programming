#include <iostream>
#include <vector>
#include <sstream>
#include <lab/atm/atm_type.hpp>
#include <lab/atm/kinds/atm.hpp>
#include <lab/atm/kinds/atm_fields.hpp>
#include <lab/atm/kinds/atm_reports.hpp>
#include <lab/tree/tree.hpp>

bool isMenu = true;

auto container = lab::Tree();

lab::ATM_reports* select_reports_atm(size_t relativeIndex) {
    auto atm_iterator = container.begin();

    size_t i = 0;

    while (i != relativeIndex) {
        if (dynamic_cast<lab::ATM_reports*>(*atm_iterator)) {
            ++i;
        }

        if (i != relativeIndex) {
            atm_iterator.next();
        }
    }

    return dynamic_cast<lab::ATM_reports*>(*atm_iterator);
}

void print_atms() {
    auto atm_iterator = container.begin();

    size_t i = 0;
    while (atm_iterator.hasNext()) {
        std::cout << ++i << ". " << *atm_iterator << std::endl;
        atm_iterator.next();
    }
}

void copy_atm() {
    print_atms();

    common::string id;

    std::cout << "Введите ID банкомата, который будет скопирован:" << std::endl;
    std::cin >> id;

    lab::ATM* atmToCopy = container.search(id);

    container.insert(atmToCopy);
}

void create_atm_constructor(lab::ATM_type type) {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите тип конструктора: " << std::endl;

        std::cout << "1. С параметрами по умолчанию" << std::endl;
        std::cout << "2. С параметрами" << std::endl;

        std::cout << std::endl;

        std::cout << "3.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        if (action_id == 1) {
            selected = true;

            if (type == lab::ATM_type::Base) {
                auto atm = new lab::ATM();
                container.insert(atm);
            }

            else if (type == lab::ATM_type::Fields) {
                auto atm = new lab::ATM_fields();
                container.insert(atm);
            }

            else if (type == lab::ATM_type::Reports) {
                auto atm = new lab::ATM_reports();
                container.insert(atm);
            }
        }

        else if (action_id == 2) {
            selected = true;

            if (type == lab::ATM_type::Base) {
                common::string id;
                std::cin >> id;

                float max_widthdraw;
                std::cin >> max_widthdraw;

                float balance;
                std::cin >> balance;

                auto atm = new lab::ATM(id, max_widthdraw, balance);
                container.insert(atm);
            }

            else if (type == lab::ATM_type::Fields) {
                common::string id;
                std::cin >> id;

                common::string bankname;
                std::cin >> bankname;

                common::string location;
                std::cin >> location;

                float max_widthdraw;
                std::cin >> max_widthdraw;

                float balance;
                std::cin >> balance;

                auto atm = new lab::ATM_fields(id, bankname, location, max_widthdraw, balance);
                container.insert(atm);
            }

            else if (type == lab::ATM_type::Reports) {
                common::string id;
                std::cin >> id;

                float max_widthdraw;
                std::cin >> max_widthdraw;

                float balance;
                std::cin >> balance;

                auto atm = new lab::ATM_reports(id, max_widthdraw, balance);
                container.insert(atm);
            }
        }

        else if (action_id == 3) {
            selected = true;
        }

        else {
            std::cout << "Неизвестная команда";
        }
    }
}

void create_atm() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите тип банкомата: " << std::endl;

        std::cout << "1. Родитель" << std::endl;
        std::cout << "2. С доп. полями" << std::endl;
        std::cout << "3. С отчётами" << std::endl;
        std::cout << "4. Скопировать" << std::endl;

        std::cout << std::endl;

        std::cout << "5.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        if (action_id == 1) {
            selected = true;
            create_atm_constructor(lab::ATM_type::Base);
        }

        else if (action_id == 2) {
            selected = true;
            create_atm_constructor(lab::ATM_type::Fields);
        }

        else if (action_id == 3) {
            selected = true;
            create_atm_constructor(lab::ATM_type::Reports);
        }

        else if (action_id == 4) {
            selected = true;
            copy_atm();
        }

        else if (action_id == 5) {
            selected = true;
        }

        else {
            std::cout << "Неизвестная команда";
        }
    }
}

void modify_atm() {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    print_atms();

    common::string id;

    std::cout << "Введите ID банкомата, который будет модифицирован:" << std::endl;
    std::cin >> id;

    auto atm = container.search(id);

    bool selected = false;

    while (!selected) {
        std::cout << "Выберите действие: " << std::endl;

        std::cout << "1. Положить деньги" << std::endl;
        std::cout << "2. Снять деньги" << std::endl;

        std::cout << std::endl;

        std::cout << "3.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        float sum;

        switch (action_id) {
        case 1:
            selected = true;

            std::cout << "Введите сумму: ";
            std::cin >> sum;

            *atm = *atm + sum;
            break;
        case 2:
            selected = true;

            std::cout << "Введите сумму: ";
            std::cin >> sum;

            *atm = *atm - sum;
            break;
        case 3:
            selected = true;
            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

void delete_atm() {
    print_atms();

    common::string id;

    std::cout << "Введите ID банкомата, который будет удалён:" << std::endl;
    std::cin >> id;

    container.erase(id);
}

void save_text() {
    std::ofstream out("ATMs.txt", std::ios::out);

    if (!out) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    auto atm_iterator = container.begin();
    while (atm_iterator.hasNext()) {
        lab::ATM_io::save_text(out, *atm_iterator);
        atm_iterator.next();
    }

    out.close();
}

void save_bin() {
    std::ofstream out("ATMs.bin", std::ios::out | std::ios::binary);

    if (!out) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    auto atm_iterator = container.begin();
    while (atm_iterator.hasNext()) {
        lab::ATM_io::save_bin(out, *atm_iterator);
        atm_iterator.next();
    }

    out.close();
}

void save_atms() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите способ: " << std::endl;

        std::cout << "1. В текстовый файл (ATMs.txt)" << std::endl;
        std::cout << "2. В бинарный файл (ATMs.bin)" << std::endl;

        std::cout << std::endl;

        std::cout << "3.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            save_text();
            break;
        case 2:
            selected = true;

            save_bin();
            break;
        case 3:
            selected = true;

            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

void clear() {
    container.clear();
}

void load_text() {
    clear();

    std::ifstream in("ATMs.txt", std::ios::in);

    if (!in) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    while (in.is_open()) {
        auto atm = lab::ATM_io::load_text(in);

        if (atm != nullptr) {
            container.insert(atm);
        }
        else {
            in.close();
        }
    }
}

void load_bin() {
    clear();

    std::ifstream in("ATMs.bin", std::ios::in | std::ios::binary);

    if (!in) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    while (in.is_open()) {
        auto atm = lab::ATM_io::load_bin(in);

        if (atm != nullptr) {
            container.insert(atm);
        }
        else {
            in.close();
        }
    }
}

void load_atms() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите способ: " << std::endl;

        std::cout << "1. Из текстового файла (ATMs.txt)" << std::endl;
        std::cout << "2. Из бинарного файла (ATMs.bin)" << std::endl;

        std::cout << std::endl;

        std::cout << "3.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            load_text();
            break;
        case 2:
            selected = true;

            load_bin();
            break;
        case 3:
            selected = true;

            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

void view_reports() {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    auto atm_iterator = container.begin();
    size_t i = 0;
    while (atm_iterator.hasNext()) {
        if (auto casted = dynamic_cast<lab::ATM_reports*>(*atm_iterator)) {
            std::cout << ++i << ". " << *casted << std::endl;
        }
        atm_iterator.next();
    }

    size_t relativeIndex = 0;

    std::cout << "Введите номер банкомата: " << std::endl;
    std::cin >> relativeIndex;

    auto selected = select_reports_atm(relativeIndex);

    std::cout << selected->log();
}

void menu() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите действие: " << std::endl;

        std::cout << "1. Создать объект" << std::endl;
        std::cout << "2. Модифицировать объект" << std::endl;
        std::cout << "3. Удалить объект" << std::endl;
        std::cout << "4. Вывести список объектов" << std::endl;
        std::cout << "5. Сохранить объекты" << std::endl;
        std::cout << "6. Загрузить объекты" << std::endl;
        std::cout << "7. Посмотреть отчёты" << std::endl;

        std::cout << std::endl;

        std::cout << "8.Выход" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            create_atm();
            break;
        case 2:
            selected = true;

            modify_atm();
            break;
        case 3:
            selected = true;

            delete_atm();
            break;
        case 4:
            selected = true;

            print_atms();
            break;
        case 5:
            selected = true;

            save_atms();
            break;
        case 6:
            selected = true;

            load_atms();
            break;
        case 7:
            selected = true;

            view_reports();
            break;
        case 8:
            selected = true;
            clear();

            isMenu = false;
            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

int main() {
    while (isMenu) {
        try {
            menu();
        }
        catch (std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }
}