project(lab_lib)
add_library(lab_lib include/lab/atm.hpp src/atm.cpp)
target_link_libraries(lab_lib PRIVATE common)
target_include_directories(lab_lib PUBLIC include)

project(lab_exe)
add_executable(lab_exe src/main.cpp)
target_link_libraries(lab_exe PRIVATE common lab_lib)
target_include_directories(lab_exe PRIVATE include)

project(lab_tests)
add_executable(lab_tests tests/atm_tests.cpp)
target_link_libraries(lab_tests PRIVATE common lab_lib CONAN_PKG::catch2)
target_include_directories(lab_tests PRIVATE include)