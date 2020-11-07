#include <vector>
#include <chrono>
#include <common/string.hpp>

namespace lab {
    enum Report_Action {
        Enabled,
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
            static std::time_t timer;
            Report_Item(Report_Action action, float sum);
            friend std::ostream& operator<<(std::ostream& out, const Report_Item& atm);
            bool is_today();
    };

    class ATM_Report {
        public:
            ATM_Report();
            ATM_Report(const ATM_Report& other);
            common::string log();
            virtual ~ATM_Report();
        protected:
            std::vector<Report_Item> reports;
    };
}