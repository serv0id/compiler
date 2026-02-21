#include <fstream>
#include <iostream>
#include "include/lox.h"

int main(const int argc, char *argv[]) {
    std::cout << "Welcome to lox compiler." << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(64);  // sysexits.h
    }

    const std::string file_name = argv[1];
    auto program = lox(file_name);

    program.run(program.read_file());

    return 0;
}