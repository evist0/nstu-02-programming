#ifndef UTILS_ATM_H
#define UTILS_ATM_H

#include <utils/String.h>

class ATM {
		private:
				Utils::String _id;
				float _balance;
				float _maxWithdraw;

		public:
				explicit ATM(const Utils::String& id);
				ATM(const Utils::String& id, float maxWithdraw);

				void DepositMoney(float amount);
				void WithdrawMoney(float amount);

				Utils::String ToString();
};

#endif //UTILS_ATM_H