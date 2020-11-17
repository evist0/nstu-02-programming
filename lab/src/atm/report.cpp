#include <iomanip>
#include <lab/atm/report.hpp>
#include <common/string.hpp>

std::ostream& lab::operator<<(std::ostream& out, const lab::Report& report) {
    auto time_t = std::chrono::system_clock::to_time_t(report.m_time);

    common::string actionString;
    bool withSum = true;

    switch (report.m_actionType) {
    case Action::Enabled:
        actionString = common::string("Enabled");
        withSum = false;
        break;
    case Action::Disabled:
        actionString = common::string("Disabled");
        withSum = false;
        break;
    case Action::Deposit:
        actionString = common::string("Deposit");
        break;
    case Action::Withdraw:
        actionString = common::string("Withdraw");
        break;
    }

    out <<
        "------------" << std::endl <<
        "Time: " << std::put_time(std::localtime(&time_t), "%X") << std::endl <<
        "Action: " << actionString << std::endl;

    if (withSum) {
        out <<
            "Sum: " << report.m_actionSum << std::endl;
    }

    out << "------------" << std::endl;

    return out;
}

std::ofstream& lab::operator<<(std::ofstream& out, const lab::Report& report) {
    out << report.m_actionType << ' '
        << std::chrono::duration_cast<std::chrono::seconds>(report.m_time.time_since_epoch()).count() << ' '
        << report.m_actionSum;

    return out;
}

bool lab::Report::is_today() {
    auto report_time_t = std::chrono::system_clock::to_time_t(this->m_time);
    auto report = std::localtime(&report_time_t);
    auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto now = std::localtime(&now_time_t);

    return report->tm_mday == now->tm_mday && report->tm_mon == now->tm_mon && report->tm_year == now->tm_year;
}

lab::Report::Report(lab::Action action, std::chrono::time_point<std::chrono::system_clock> time, float sum) {
    this->m_actionType = action;
    this->m_time = time;
    this->m_actionSum = sum;
}

/*lab::Report lab::Report::from_binary(std::ifstream& in) {
}*/

/*void lab::Report::to_binary() {

}*/

lab::Report lab::Report::from_text(std::ifstream& in) {
    Action type;
    std::chrono::system_clock::duration::rep time;
    float sum;

    in >> type >> time >> sum;

    return {type, std::chrono::system_clock::time_point(std::chrono::seconds(time)), sum};
}
