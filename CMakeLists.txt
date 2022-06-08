cmake_minimum_required(VERSION 3.22)
project(C_tests)
set(CMAKE_CXX_STANDARD 14)

add_executable(task_13_demo
        main.cpp

        C-solution/const.h

        C-solution/Int/Int.h
        C-solution/Int/Int.cpp
        C-solution/Int/task_3/task_3.cpp

        C-solution/Polynom/Polynom.h
        C-solution/Polynom/Polynom.cpp

        main.cpp)