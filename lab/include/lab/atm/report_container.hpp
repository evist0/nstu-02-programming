#ifndef OOP_LABS_REPORT_CONTAINER_HPP
#define OOP_LABS_REPORT_CONTAINER_HPP
#include <lab/atm/report.hpp>

namespace lab {
    class Report_Container {
        public:
            Report_Container();
            Report_Container(const Report_Container& rhs) = delete;
            Report_Container& operator=(const Report_Container& rhs) = delete;
            Report& operator[](int);
            size_t length() const;
            size_t capacity() const;
            void push_back(Report report);
            void clear();
            ~Report_Container();
        private:
            void realloc();
            Report* m_container;
            size_t m_length;
            size_t m_capacity;
    };
}

#endif //OOP_LABS_REPORT_CONTAINER_HPP
