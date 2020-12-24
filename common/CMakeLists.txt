project(common)

add_library(common
        include/common/string.hpp
        include/common/stack.hpp
        src/string.cpp
        )
target_include_directories(common PUBLIC include)