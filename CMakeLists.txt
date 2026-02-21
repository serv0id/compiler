cmake_minimum_required(VERSION 4.1)
project(compiler)

set(CMAKE_CXX_STANDARD 20)


add_library(core
        src/lox.cpp
        src/token.cpp
        src/scanner.cpp
)

target_include_directories(core PUBLIC include)

add_executable(compiler main.cpp)
target_link_libraries(compiler PRIVATE core)

add_executable(tests
        tests/lexer.cpp
)
target_link_libraries(tests PRIVATE core)
