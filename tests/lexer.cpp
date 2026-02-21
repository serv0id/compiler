#include <iostream>
#include "lox.h"

int main() {
    std::cout << "Testing suite for the lexer!" << std::endl;

    auto program = lox("test.lox");

    program.run(program.read_file());
}
