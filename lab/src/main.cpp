#include <iostream>
#include <memory>
#include <lab/tree/tree.hpp>
#include <lab/atm/atm_type.hpp>
#include <lab/atm/kinds/atm_fields.hpp>
#include <lab/atm/kinds/atm_reports.hpp>

auto int_tree = lab::Tree<int>();

auto float_tree = lab::Tree<float>();

auto atm_tree = lab::Tree<lab::ATM>();

short selected_tree = 0;

bool isMenu = true;

void switch_tree() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите новый тип дерева: " << std::endl;

        std::cout << "1. Целочисленный" << std::endl;
        std::cout << "2. С плавающей запятой" << std::endl;
        std::cout << "3. С банкоматами" << std::endl;

        std::cout << std::endl;

        std::cout << "4.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        if (action_id == 1) {
            selected = true;
            selected_tree = 0;
        }

        else if (action_id == 2) {
            selected = true;
            selected_tree = 1;
        }

        else if (action_id == 3) {
            selected = true;
            selected_tree = 2;
        }

        else if (action_id == 4) {
            selected = true;
        }

        else {
            std::cout << "Неизвестная команда";
        }
    }
}

void print() {
    if (selected_tree == 0) {
        if (int_tree.empty()) {
            std::cout << "Список пуст!" << std::endl;
            return;
        }

        auto iterator = int_tree.begin();

        while (iterator.hasNext()) {
            iterator.next();
            std::cout << **iterator << std::endl;
        }
    }
    else if (selected_tree == 1) {
        if (float_tree.empty()) {
            std::cout << "Список пуст!" << std::endl;
            return;
        }

        auto iterator = float_tree.begin();

        while (iterator.hasNext()) {
            iterator.next();
            std::cout << **iterator << std::endl;
        }
    }
    else if (selected_tree == 2) {
        if (atm_tree.empty()) {
            std::cout << "Список пуст!" << std::endl;
            return;
        }

        auto atm_iterator = atm_tree.begin();

        size_t i = 0;
        while (atm_iterator.hasNext()) {
            atm_iterator.next();
            std::cout << ++i << ". " << **atm_iterator << std::endl;
        }
    }
}

void copy_atm() {
    print();

    common::string id;

    std::cout << "Введите ID банкомата, который будет скопирован:" << std::endl;
    std::cin >> id;

    lab::ATM* atmToCopy = atm_tree.search(id);

    atm_tree.insert(*atmToCopy);
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
                atm_tree.insert(*atm);
            }

            else if (type == lab::ATM_type::Fields) {
                auto atm = new lab::ATM_fields();
                atm_tree.insert(*atm);
            }

            else if (type == lab::ATM_type::Reports) {
                auto atm = new lab::ATM_reports();
                atm_tree.insert(*atm);
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
                atm_tree.insert(*atm);
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
                atm_tree.insert(*atm);
            }

            else if (type == lab::ATM_type::Reports) {
                common::string id;
                std::cin >> id;

                float max_widthdraw;
                std::cin >> max_widthdraw;

                float balance;
                std::cin >> balance;

                auto atm = new lab::ATM_reports(id, max_widthdraw, balance);
                atm_tree.insert(*atm);
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
            if (!atm_tree.empty()) {
                copy_atm();
            }
        }

        else if (action_id == 5) {
            selected = true;
        }

        else {
            std::cout << "Неизвестная команда";
        }
    }
}

void add_to_tree() {
    if (selected_tree == 0) {
        int input;
        std::cin >> input;

        int_tree.insert(input);
    }
    else if (selected_tree == 1) {
        float input;
        std::cin >> input;

        float_tree.insert(input);
    }
    else if (selected_tree == 2) {
        create_atm();
    }
}

void erase_from_tree() {
    if (selected_tree == 0) {
        int input;
        std::cin >> input;

        int_tree.erase(input);
    }
    else if (selected_tree == 1) {
        float input;
        std::cin >> input;

        float_tree.erase(input);
    }
    else if (selected_tree == 2) {
        common::string id;
        std::cin >> id;

        atm_tree.erase(id);
    }
}

void save_tree() {
    if (selected_tree == 0) {
        std::ofstream out("int.bin", std::ios::out | std::ios::binary);
        int_tree.write(out);
    }
    else if (selected_tree == 1) {
        std::ofstream out("float.bin", std::ios::out | std::ios::binary);
        float_tree.write(out);
    }
    else if (selected_tree == 2) {
        std::ofstream out("ATMs.bin", std::ios::out | std::ios::binary);
        atm_tree.write(out);
    }
}

void load_tree() {
    if (selected_tree == 0) {
        std::ifstream in("int.bin", std::ios::out | std::ios::binary);
        int_tree = lab::Tree<int>::read(in);

    }
    else if (selected_tree == 1) {
        std::ifstream in("float.bin", std::ios::out | std::ios::binary);
        float_tree = lab::Tree<float>::read(in);
    }
    else if (selected_tree == 2) {
        std::ifstream in("ATMs.bin", std::ios::out | std::ios::binary);
        atm_tree = lab::Tree<lab::ATM>::read(in);
    }
}

void menu() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите действие: " << std::endl;

        std::cout << "1. Заменить дерево" << std::endl;
        std::cout << "2. Добавить в дерево" << std::endl;
        std::cout << "3. Удалить объект из дерева" << std::endl;
        std::cout << "4. Вывести дерево" << std::endl;
        std::cout << "5. Сохранить дерево" << std::endl;
        std::cout << "6. Загрузить дерево" << std::endl;

        std::cout << std::endl;

        std::cout << "7.Выход" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            switch_tree();
            break;
        case 2:
            selected = true;

            add_to_tree();
            break;
        case 3:
            selected = true;

            erase_from_tree();
            break;
        case 4:
            selected = true;

            print();
            break;
        case 5:
            selected = true;

            save_tree();
            break;
        case 6:
            selected = true;

            load_tree();
            break;
        case 7:
            selected = true;

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