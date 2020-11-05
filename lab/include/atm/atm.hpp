#include <iosfwd>
#include <fstream>
#include "atm_base.hpp"
#include "atm_report.hpp"

namespace lab {
    class ATM: public ATM_Base, protected ATM_Report {
        public:
            ATM();

            ATM(const common::string& bankName,
                    const common::string& location,
                    const common::string& id,
                    float maxWithdraw,
                    float initialBalance);

            common::string bankName();
            common::string location();

            friend std::istream& operator>>(std::istream &in, const ATM& atm);

            friend std::ostream& operator<<(std::ostream &out, const ATM& atm);

            friend std::ifstream& operator>>(std::ifstream &in, const ATM& atm);

            friend std::ofstream& operator<<(std::ofstream &out, const ATM& atm);

            static lab::ATM from_binary(std::ifstream &in);

            std::ofstream& to_binary(std::ofstream &out);
        private:
            common::string m_bankName;
            common::string m_location;
    };
}