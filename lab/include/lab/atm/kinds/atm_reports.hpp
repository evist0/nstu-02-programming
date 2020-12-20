#ifndef ATM_REPORTS_H
#define ATM_REPORTS_H
#include <chrono>
#include <common/string.hpp>
#include <lab/atm/kinds/atm.hpp>
#include <lab/atm/report.hpp>
#include <lab/atm/report_container.hpp>

namespace lab {
    class ATM_reports : public ATM {
        public:
            Report_Container reports;

            ATM_reports(const lab::ATM_reports& atm);

            ATM_reports(const common::string& id = "not_provided", float max_withdraw = 0.f,
                    float initial_balance = 0.f, bool loaded = false);

            ATM_reports& operator=(const lab::ATM_reports& other);

            size_t reports_amount() const;
            common::string log();

            void deposit(float amount) override;
            void withdraw(float amount) override;

            friend class ATM_io;

            ~ATM_reports() override;
        private:
            static ATM* load_text(std::ifstream& in);
            void save_text(std::ofstream& out) override;
            static ATM* load_bin(std::ifstream& in);
            void save_bin(std::ofstream& out) override;

            void write(std::ostream& out) override;
            void read(std::istream& in) override;
    };
}

#endif //ATM_REPORTS_H