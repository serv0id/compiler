cmake_minimum_required(VERSION 4.1)
project(compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler main.cpp
        lox.cpp
        include/lox.h
        include/tokentype.h
        token.cpp
        include/token.h
        scanner.cpp
        include/scanner.h)
