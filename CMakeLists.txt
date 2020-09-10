cmake_minimum_required(VERSION 3.17)

project(main)
add_executable(main main.cpp)
target_include_directories(main PUBLIC include)
target_link_libraries(main utils lab1)

project(utils)
add_library(utils include/utils/String.h src/utils/String.cpp)
target_include_directories(utils PUBLIC include/utils)
target_include_directories(utils PRIVATE src/utils)

project(lab1)
add_library(lab1 include/lab1/atm.h src/lab1/atm.cpp)
target_include_directories(lab1 PUBLIC include)