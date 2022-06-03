cmake_minimum_required(VERSION 3.22)
project(C_tests)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(C_tests
        main_tests.cpp
        Polynom_tests.cpp

        C-solution/const.h

        C-solution/Int/Int.h
        C-solution/Int/Int.cpp
        C-solution/Int/task_4/task_4.cpp

        C-solution/Polynom/Polynom.h
        C-solution/Polynom/Polynom.cpp)

target_link_libraries(C_tests gtest gtest_main)