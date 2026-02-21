#include "../include/lox.h"
#include <fstream>
#include <iostream>
#include <utility>
#include "../include/scanner.h"

bool lox::had_error = false;

lox::lox(const std::string &file_name) {
    file = file_name;
}

std::string lox::read_file() const {
    std::ifstream filestream(this->file, std::ios::binary);
    std::string file_contents{std::istreambuf_iterator<char>(filestream),
                              std::istreambuf_iterator<char>()};

    return file_contents;
}

void lox::error(const int line, const std::string& message) {
    report(line, "", message);
}

void lox::report(const int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
    had_error = true;
}

int lox::run(std::string code) {
    scanner scanner(std::move(code));
    if (had_error) {
        std::cout << "Exiting due to error(s)";
        exit(65);
    }
    return 0;
}
