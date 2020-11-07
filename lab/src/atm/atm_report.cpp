#include <atm/atm_report.hpp>
#include <sstream>

std::time_t lab::Report_Item::timer = std::time(nullptr);

lab::Report_Item::Report_Item(Report_Action action, float sum) {
    this->m_time = std::localtime(&timer);
    this->m_actionType = action;
    this->m_actionSum = sum;
}

std::ostream& lab::operator<<(std::ostream& out, const Report_Item& report) {
    common::string actionString;
    bool withSum = true;

    switch (report.m_actionType) {
    case Enabled:
        actionString = common::string("Enabled");
        withSum = false;
        break;
    case Disabled:
        actionString = common::string("Disabled");
        withSum = false;
        break;
    case Deposit:
        actionString = common::string("Deposit");
        break;
    case Withdraw:
        actionString = common::string("Withdraw");
        break;
    }

    out <<
        "Time: " << report.m_time->tm_hour << ':' << report.m_time->tm_min << ':' << report.m_time->tm_hour << std::endl
        <<
        "Action: " << actionString << std::endl;

    if (withSum) {
        out <<
            "Sum: " << report.m_actionSum << std::endl;
    }

    return out;
}

bool lab::Report_Item::is_today() {
    auto now = std::localtime(&timer);

    return now == this->m_time;
}

lab::ATM_Report::ATM_Report() {
    this->reports = std::vector<Report_Item>();

    this->reports.emplace_back(Report_Action::Enabled, 0);
}

lab::ATM_Report::ATM_Report(const lab::ATM_Report& other) {
    this->reports = other.reports;
}

common::string lab::ATM_Report::log() {
    std::stringstream ss;
    auto iterator = this->reports.begin();

    for (; iterator != this->reports.end(); iterator++) {
        if (iterator->is_today()) {
            ss << *iterator;
        }
    }

    return common::string(ss.str());
}

lab::ATM_Report::~ATM_Report() {
    this->reports.emplace_back(Report_Action::Disabled, 0);
}
