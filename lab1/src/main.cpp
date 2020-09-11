#include <iostream>
#include <lab1/atm.hpp>

int main() {
    lab1::ATM atm = lab1::ATM("id9382");

    std::cout << atm.to_string();
}