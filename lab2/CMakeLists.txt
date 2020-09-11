project(lab2_lib)
add_library(lab2_lib include/lab2/atm.hpp src/atm.cpp)
target_link_libraries(lab2_lib PRIVATE common lab1_lib)
target_include_directories(lab2_lib PRIVATE include)

project(lab2_exe)
add_executable(lab2_exe src/main.cpp)
target_link_libraries(lab2_exe PRIVATE common lab1_lib lab2_lib)
target_include_directories(lab2_exe PRIVATE include)


project(lab2_tests)
add_executable(lab2_tests tests/atm_tests.cpp)
target_link_libraries(lab2_tests PRIVATE common lab1_lib lab2_lib CONAN_PKG::catch2)
target_include_directories(lab2_tests PRIVATE include)