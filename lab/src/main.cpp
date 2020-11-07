#include <iostream>
#include <vector>
#include <atm/atm.hpp>
#include <sstream>

bool isMenu = true;

std::vector<lab::ATM> container = std::vector<lab::ATM>();

void menu();

lab::ATM* select_object(size_t listIndex);

void input_atm();

void copy_atm();

void create_object();

void modify_object();

void delete_object();

void print_objects();

void show_logs();

void save_objects();

void save_text();

void save_bin();

void load_objects();

void load_text();

void load_bin();

int main() {
    while (isMenu) {
        menu();
    }
}

void menu() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите действие: " << std::endl;

        std::cout << "1. Создать объект" << std::endl;
        std::cout << "2. Модифицировать объект" << std::endl;
        std::cout << "3. Удалить объект" << std::endl;
        std::cout << "4. Вывести список объектов" << std::endl;
        std::cout << "5. Посмотреть логи" << std::endl;
        std::cout << "6. Сохранить объекты" << std::endl;
        std::cout << "7. Загрузить объекты" << std::endl;

        std::cout << std::endl;

        std::cout << "8.Выход" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            create_object();
            break;
        case 2:
            selected = true;

            modify_object();
            break;
        case 3:
            selected = true;

            delete_object();
            break;
        case 4:
            selected = true;

            print_objects();
            break;
        case 5:
            selected = true;

            show_logs();
            break;
        case 6:
            selected = true;

            save_objects();
            break;
        case 7:
            selected = true;

            load_objects();
            break;
        case 8:
            selected = true;

            isMenu = false;
            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

lab::ATM* select_object(size_t listIndex) {
    return &container[listIndex - 1];
}

void input_atm() {
    auto atm = new lab::ATM;

    std::cin >> *atm;

    container.push_back(*atm);

    delete atm;
}

void copy_atm() {
    print_objects();

    size_t listIndex;

    std::cout << "Введите номер банкомата в списке, который будет скопирован:" << std::endl;
    std::cin >> listIndex;

    lab::ATM* atmToCopy = select_object(listIndex);

    container.emplace_back(*atmToCopy);
}

void create_object() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите конструктор: " << std::endl;

        std::cout << "1. По умолчанию" << std::endl;
        std::cout << "2. С аргументами" << std::endl;
        std::cout << "3. Копирования" << std::endl;

        std::cout << std::endl;

        std::cout << "4.Назад" << std::endl;

        int action_id = 0;

        std::cin >> action_id;

        switch (action_id) {
        case 1:
            selected = true;

            container.emplace_back();
            break;
        case 2:
            selected = true;

            input_atm();
            break;
        case 3:
            selected = true;

            copy_atm();
            break;
        case 4:
            selected = true;

            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
}

void modify_object() {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    print_objects();

    size_t listIndex;

    std::cout << "Введите номер банкомата в списке, который будет модифицирован:" << std::endl;
    std::cin >> listIndex;

    auto atm = select_object(listIndex);

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

void delete_object() {
    print_objects();

    size_t listIndex;

    std::cout << "Введите номер банкомата в списке, который будет удалён:" << std::endl;
    std::cin >> listIndex;

    auto ptr = container.cbegin() + listIndex - 1;

    container.erase(ptr);
}

void print_objects() {
    auto atm_iterator = container.begin();
    size_t i = 0;
    for (; atm_iterator != container.end(); atm_iterator++) {
        std::cout << ++i << ". " << *atm_iterator;
    }
}

void show_logs() {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    print_objects();

    size_t listIndex;

    std::cout << "Введите номер банкомата в списке:" << std::endl;
    std::cin >> listIndex;

    auto atm = select_object(listIndex);

    std::cout << atm->log();
}

void save_objects() {
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

void save_text() {
    std::ofstream out("ATMs.txt", std::ios::out);

    if (!out) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    auto atm_iterator = container.begin();
    for (; atm_iterator != container.end(); atm_iterator++) {
        out << *atm_iterator;
    }

    out.close();
}

void save_bin() {
    std::ofstream out("ATMs.bin", std::ios::out | std::ios::binary);

    if (!out) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    auto atm_iterator = container.begin();
    for (; atm_iterator != container.end(); atm_iterator++) {
        atm_iterator->to_binary(out);
    }

    out.close();
}

void load_objects() {
    bool selected = false;

    while (!selected) {
        std::cout << "Выберите способ: " << std::endl;

        std::cout << "1. Из текстового файла (ATMs.txt)" << std::endl;
        std::cout << "2. Из бинарного файл (ATMs.bin)" << std::endl;

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

void load_text() {
    container.clear();

    std::ifstream in("ATMs.txt", std::ios::in);

    if (!in) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    while (true) {
        common::string id;
        common::string bank;
        common::string location;
        float balance;
        float max_withdraw;

        in >> id >> bank >> location >> balance >> max_withdraw;

        if (in.eof()) {
            in.close();
            return;
        }

        container.emplace_back(bank, location, id, balance, max_withdraw);
    }
}

void load_bin() {
    container.clear();

    std::ifstream in("ATMs.bin", std::ios::in | std::ios::binary);

    if (!in) {
        throw std::runtime_error("Невозможно открыть файл");
    }

    while (true) {

        lab::ATM new_atm = lab::ATM::from_binary(in);

        if (in.eof()) {
            in.close();
            return;
        }

        container.push_back(new_atm);
    }
}