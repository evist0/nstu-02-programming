#include <iostream>
#include <lab1/atm.hpp>

int main() {
    lab1::ATM atm_0 = lab1::ATM();
    lab1::ATM atm_1 = lab1::ATM("id9382", 20.5f, 500.5f);
    lab1::ATM atm_2 = lab1::ATM(atm_1);

    std::cout << "ATM Amount: " << lab1::ATM::get_atm_amount() << std::endl;

    std::cout << atm_0.to_string();
    std::cout << atm_1.to_string();
    std::cout << atm_2.to_string();

    atm_1.withdraw(15.f);

    std::cout << atm_1.to_string();
    std::cout << atm_2.to_string();

    atm_2.deposit(50.f);

    std::cout << atm_2.to_string();
}