#ifndef ATM_REPORTS_H
#define ATM_REPORTS_H
#include <chrono>
#include <vector>
#include <common/string.hpp>
#include <lab/atm/kinds/atm.hpp>
#include <lab/atm/report.hpp>

namespace lab {
    class ATM_reports : public ATM {
        public:
            std::vector<Report> reports;

            ATM_reports(const lab::ATM_reports& atm);

            ATM_reports(const common::string& id = "not_provided", float max_withdraw = 0.f,
                    float initial_balance = 0.f, bool loaded = false);

            ATM_reports& operator=(const lab::ATM_reports& other);

            size_t reports_amount() const;
            common::string log();

            void deposit(float amount) override;
            void withdraw(float amount) override;

            ~ATM_reports() override;
        private:
            void write(std::ostream& out) override;
            void read(std::istream& in) override;
    };
}

#endif //ATM_REPORTS_H