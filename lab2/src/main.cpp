#include <iostream>
#include <lab2/atm.hpp>

int main() {
    lab2::ATM atm = lab2::ATM("id9382");

    std::cout << (atm != 0.0f);
}