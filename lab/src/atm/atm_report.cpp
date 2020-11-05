#include <atm/atm_report.hpp>

lab::Report_Item::Report_Item(Report_Action action, float sum) {
    std::time_t timer = std::time(nullptr);

    this->m_time = std::localtime(&timer);
    this->m_actionType = action;
    this->m_actionSum = sum;
}

std::ofstream& lab::operator<<(std::ofstream& out, const Report_Item& report) {
    common::string actionString;
    bool withSum = true;

    switch (report.m_actionType) {
    case Created:
        actionString = common::string("Created");
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
        "<- REPORT ->" << std::endl <<
        "Time: " << report.m_time->tm_hour << ':' << report.m_time->tm_min << ':' << report.m_time->tm_hour << std::endl
        <<
        "Action: " << actionString << std::endl;

    if (withSum) {
        out <<
            "Sum: " << report.m_actionSum << std::endl;
    }

    return out;
}

