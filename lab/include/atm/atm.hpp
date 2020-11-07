#include <iosfwd>
#include <fstream>
#include "atm_base.hpp"
#include "atm_report.hpp"

namespace lab {
    class ATM : public ATM_Base, public ATM_Report {
        public:
            ATM();

            ATM(const common::string& bankName,
                    const common::string& location,
                    const common::string& id,
                    float maxWithdraw,
                    float initialBalance);

            ATM(const ATM& atm);

            common::string bankName() const noexcept;
            common::string location() const noexcept;

            ATM& operator=(const ATM& atm);

            friend ATM operator-(ATM& atm, float withdrawSum);

            friend ATM operator+(ATM& atm, float depositSum);

            friend std::istream& operator>>(std::istream& in, ATM& atm);

            friend std::ostream& operator<<(std::ostream& out, const ATM& atm);

            friend std::ifstream& operator>>(std::ifstream& in, ATM& atm);

            friend std::ofstream& operator<<(std::ofstream& out, const ATM& atm);

            void deposit(float amount) override;
            void withdraw(float amount) override;

            static ATM from_binary(std::ifstream& in);

            std::ofstream& to_binary(std::ofstream& out);
        private:
            common::string m_bankName;
            common::string m_location;
    };

    ATM operator-(ATM& atm, float withdrawSum);

    ATM operator+(ATM& atm, float depositSum);

    bool operator==(ATM& atm, float checkSum);

    bool operator!=(ATM& atm, float checkSum);

    std::istream& operator>>(std::istream& in, const ATM& atm);

    std::ostream& operator<<(std::ostream& out, const ATM& atm);

    std::ifstream& operator>>(std::ifstream& in, const ATM& atm);

    std::ofstream& operator<<(std::ofstream& out, const ATM& atm);
}