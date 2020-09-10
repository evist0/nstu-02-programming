cmake_minimum_required(VERSION 3.16)
project(oop-labs)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES catch2/2.13.0
        BASIC_SETUP
        BUILD missing
        CMAKE_TARGETS)

add_subdirectory(common)
add_subdirectory(lab1)