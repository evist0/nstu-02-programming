project(lab_lib)
add_library(lab_lib
        include/lab/atm/kinds/atm.hpp
        include/lab/atm/kinds/atm_fields.hpp
        include/lab/atm/report.hpp
        include/lab/atm/kinds/atm_reports.hpp
        include/lab/atm/atm_type.hpp
        include/lab/atm/atm_io.hpp
        include/lab/atm/report_container.hpp
        include/lab/tree/tree.hpp
        include/lab/tree/node.hpp
        include/lab/tree/tree_iterator.hpp
        src/atm/kinds/atm.cpp
        src/atm/kinds/atm_fields.cpp
        src/atm/report.cpp
        src/atm/kinds/atm_reports.cpp
        src/atm/atm_io.cpp
        src/atm/report_container.cpp)
target_link_libraries(lab_lib PUBLIC common)
target_include_directories(lab_lib PUBLIC include)

project(lab_exe)
add_executable(lab_exe src/main.cpp)
target_link_libraries(lab_exe PUBLIC common lab_lib)
target_include_directories(lab_exe PRIVATE include)
