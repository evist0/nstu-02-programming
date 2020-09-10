#include <lab1/atm.h>
#include <sstream>

ATM::ATM(const Utils::String& id) {
		_id = id;
		_balance = 0;
		_maxWithdraw = 0;
}

ATM::ATM(const Utils::String& id, float maxWithdraw) {
		if (maxWithdraw < 0) {
				throw std::exception();
		}

		_id = id;
		_balance = 0;
		_maxWithdraw = maxWithdraw;
}

void ATM::DepositMoney(float amount) {
		if (amount < 0) {
				throw std::exception();
		}

		_balance += amount;
}

void ATM::WithdrawMoney(float amount) {
		if (amount < 0) {
				throw std::exception();
		}

		if (_balance - amount < 0) {
				throw std::exception();
		}

		_balance -= amount;
}

Utils::String ATM::ToString() {
		return Utils::String("ATM ID: ") + _id + Utils::String("\n")
		+ Utils::String("Balance: ") + Utils::String(std::to_string(_balance)) + Utils::String("\n")
		+ Utils::String("Max withdraw: ") + Utils::String(std::to_string(_maxWithdraw)) + Utils::String("\n");
}