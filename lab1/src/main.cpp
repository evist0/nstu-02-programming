#include <iostream>
#include <vector>
#include <iterator>
#include <lab1/atm.hpp>

bool isMenu = true;
std::vector<lab1::ATM> container = std::vector<lab1::ATM>();

void input_atm();

void copy_atm();

void create_object();

void modify_object();

void delete_object();

void print_objects();

lab1::ATM* select_object(size_t listIndex);

void menu();

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

        std::cout << std::endl;

        std::cout << "5.Выход" << std::endl;

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

            isMenu = false;
            break;
        default:
            std::cout << "Неизвестная команда";
            break;
        }
    }
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

            atm->deposit(sum);
            break;
        case 2:
            selected = true;

            std::cout << "Введите сумму: ";
            std::cin >> sum;

            atm->withdraw(sum);
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
        std::cout << ++i << ". " << atm_iterator->to_string();
    }
}

void input_atm() {
    common::string id;
    float maxWithdraw, balance;

    std::cout << "Введите ID банкомата: " << std::endl;
    std::cin >> id;

    std::cout << "Введите максимальную сумму вывода: " << std::endl;
    std::cin >> maxWithdraw;

    std::cout << "Введите начальный баланс банкомата: " << std::endl;
    std::cin >> balance;

    container.emplace_back(id, maxWithdraw, balance);
}

void copy_atm() {
    print_objects();

    size_t listIndex;

    std::cout << "Введите номер банкомата в списке, который будет скопирован:" << std::endl;
    std::cin >> listIndex;

    auto atmToCopy = select_object(listIndex);

    container.emplace_back(*atmToCopy);
}

lab1::ATM* select_object(size_t listIndex) {
    return &container[listIndex - 1];
}