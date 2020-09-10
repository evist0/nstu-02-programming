project(lab1)
add_library(lab1 include/lab1/atm.hpp src/atm.cpp)
target_link_libraries(lab1 PRIVATE common)
target_include_directories(lab1 PRIVATE include)

project(lab1_tests)
add_executable(lab1_tests tests/atm_tests.cpp)
target_link_libraries(lab1_tests PRIVATE common lab1 CONAN_PKG::catch2)
target_include_directories(lab1_tests PRIVATE include)