#include <iostream>
#include <lab1/atm.h>

int main() {
		auto myATM = new ATM(Utils::String("1id53s"));

		std::cout << myATM->ToString();
}
