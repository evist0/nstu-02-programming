#ifndef ATM_FIELDS_H
#define ATM_FIELDS_H
#include <common/string.hpp>
#include "atm.hpp"

namespace lab {
    class ATM_fields: public ATM {
        public:
            ATM_fields(const lab::ATM_fields& atm);
            ATM_fields(
                    const common::string& id = "not_provided",
                    const common::string& bankname = "not_provided",
                    const common::string& location = "not_provided",
                    float max_withdraw = 0.f,
                    float initial_balance = 0.f);
            ATM_fields& operator=(const lab::ATM_fields& other);

            const char* bankname();
            const char* location();

        private:
            common::string* m_bankname;
            common::string* m_location;
            void write(std::ostream &out) override;
            void read(std::istream &in) override;
    };
}
#endif //ATM_FIELDS_H