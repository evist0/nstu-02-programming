#include <common/string.hpp>
#include <lab1/atm.hpp>
#include <lab2/atm.hpp>

lab2::ATM lab2::operator-(lab2::ATM& atm, float withdrawSum) {
    atm.withdraw(withdrawSum);
    return atm;
}

lab2::ATM lab2::operator+(lab2::ATM& atm, float depositSum) {
    atm.deposit(depositSum);
    return atm;
}

bool lab2::operator==(lab2::ATM& atm, float checkSum) {
    return atm.balance() == checkSum;
}

bool lab2::operator!=(lab2::ATM& atm, float checkSum) {
    return atm.balance() != checkSum;;
}

common::string lab2::ATM::operator()() {
    return to_string();
}