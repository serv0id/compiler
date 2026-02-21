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

include(FetchContent)
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG        v0.9.7
)
FetchContent_MakeAvailable(magic_enum)

target_link_libraries(core PRIVATE magic_enum::magic_enum)
