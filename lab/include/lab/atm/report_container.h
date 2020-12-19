#ifndef OOP_LABS_REPORT_CONTAINER_H
#define OOP_LABS_REPORT_CONTAINER_H
#include <lab/atm/report.hpp>

namespace lab {
    class Report_Container {
        public:
            Report_Container();
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

#endif //OOP_LABS_REPORT_CONTAINER_H