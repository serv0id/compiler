#include <iostream>
#include "lox.h"
#include "astprinter.h"

int ast() {
    std::unique_ptr<expr> expression =
        std::make_unique<binary>(
            std::make_unique<unary>(
                token(MINUS, "-", 1, nullptr),
                std::make_unique<literal>(123.0)
            ),
            token(STAR, "*", 1, nullptr),
            std::make_unique<grouping>(
                std::make_unique<literal>(45.67)
            )
        );

    astprinter printer;
    std::cout << printer.print(*expression) << std::endl;

    return 0;
}

int main() {
    std::cout << "Testing suite for the lexer!" << std::endl;
    auto program = lox("../tests/lexer.lox");

    // program.run(program.read_file());
    ast();

    return 0;
}


