project(common)

add_library(common include/common/string.hpp src/string.cpp)
target_include_directories(common PUBLIC include)

project(common_tests)
add_executable(common_tests tests/string_test.cpp)
target_link_libraries(common_tests common CONAN_PKG::catch2)