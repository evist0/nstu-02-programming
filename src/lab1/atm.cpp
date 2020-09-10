#include <utils/String.h>
#include <sstream>
#include <lab1/atm.h>

ATM::ATM(const Utils::String& id) {
		_id = id;
		_balance = 0;
		_maxWithdraw = 0;
}

ATM::ATM(const Utils::String& id, float maxWithdraw) {
		if (maxWithdraw < 0) {
				throw std::exception("Max withdraw can not be less than 0");
		}

		_id = id;
		_balance = 0;
		_maxWithdraw = maxWithdraw;
}

void ATM::DepositMoney(float amount) {
		if (amount < 0) {
				throw std::exception("You can not upload negative amount of money");
		}

		_balance += amount;
}

void ATM::WithdrawMoney(float amount) {
		if (amount < 0) {
				throw std::exception("You can not withdraw negative amount of money");
		}

		if (_balance - amount < 0) {
				throw std::exception("Not enough money in the ATM, try a different amount");
		}

		_balance -= amount;
}

Utils::String ATM::ToString() {
		return Utils::String("ATM ID: ") + _id + Utils::String("\n")
		+ Utils::String("Balance: ") + Utils::String(std::to_string(_balance)) + Utils::String("\n")
		+ Utils::String("Max withdraw: ") + Utils::String(std::to_string(_maxWithdraw)) + Utils::String("\n");
}
