#ifndef REPORT_H
#define REPORT_H
#include <chrono>
#include <iostream>

namespace lab {
    enum class Action {
            Enabled,
            Deposit,
            Withdraw,
            Disabled,
    };

    inline std::istream& operator>>(std::istream& in, lab::Action& type) {
        std::underlying_type_t<lab::Action> number;
        in >> number;

        switch (static_cast<lab::Action>(number)) {
        case Action::Enabled:
            type = lab::Action::Enabled;
            break;
        case Action::Deposit:
            type = lab::Action::Deposit;
            break;
        case Action::Withdraw:
            type = lab::Action::Withdraw;
            break;
        case Action::Disabled:
            type = lab::Action::Disabled;
            break;
        }

        return in;
    }

    inline std::ostream& operator<<(std::ostream& out, const lab::Action& type) {
        out << static_cast<int>(type);

        return out;
    }

    class Report {
        private:
            std::chrono::time_point<std::chrono::system_clock> m_time;
            Action m_actionType;
            float m_actionSum{};
        public:
            void to_binary(std::ofstream& out);
            static Report from_binary(std::ifstream& in);
            Report();
            Report(Action action, std::chrono::time_point<std::chrono::system_clock> time, float sum);
            friend std::ostream& operator<<(std::ostream& out, const Report& report);
            friend std::ofstream& operator<<(std::ofstream& out, const Report& report);
            static Report from_text(std::ifstream& in);
            bool is_today();
    };

    std::ostream& operator<<(std::ostream& out, const Report& report);
    std::ofstream& operator<<(std::ofstream& out, const Report& report);
}
#endif