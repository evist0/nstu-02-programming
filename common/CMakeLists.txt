project(common)

add_library(common include/common/string.hpp src/string.cpp)
target_include_directories(common PUBLIC include)