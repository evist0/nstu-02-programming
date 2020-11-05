#include <vector>
#include <chrono>
#include <common/string.hpp>

namespace lab {
    enum Report_Action {
        Created,
        Deposit,
        Withdraw,
        Disabled,
    };

    class Report_Item {
        private:
            std::tm* m_time;
            Report_Action m_actionType;
            float m_actionSum;
        public:
            Report_Item(Report_Action action, float sum);
            friend std::ofstream& operator<<(std::ofstream& out, const Report_Item& atm);
    };

    class ATM_Report {
        protected:
            std::vector<Report_Item> reports;
    };
}