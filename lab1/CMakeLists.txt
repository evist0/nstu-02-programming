project(lab1_lib)
add_library(lab1_lib include/lab1/atm.hpp src/atm.cpp)
target_link_libraries(lab1_lib PRIVATE common)
target_include_directories(lab1_lib PUBLIC include)

project(lab1_exe)
add_executable(lab1_exe src/main.cpp)
target_link_libraries(lab1_exe PRIVATE common lab1_lib)
target_include_directories(lab1_exe PRIVATE include)


project(lab1_tests)
add_executable(lab1_tests tests/atm_tests.cpp)
target_link_libraries(lab1_tests PRIVATE common lab1_lib CONAN_PKG::catch2)
target_include_directories(lab1_tests PRIVATE include)