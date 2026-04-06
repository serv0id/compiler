#include "lox.h"
#include "scanner.h"
#include <fstream>
#include <iostream>
#include <utility>
#include "astprinter.h"
#include "parser.h"


bool lox::had_error = false;
bool lox::had_runtime_error = false;
interpreter lox::interp = interpreter();

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

void lox::error(const token& token, const std::string& string) {
    if (token.get_type() == EOFF) {
        report(token.get_line(), "at end", string);
    } else {
        report(token.get_line(), " at '" + token.get_lexeme() + "'", string);
    }
}

void lox::report(const int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
    had_error = true;
}

void lox::runtime_error(RuntimeError e) {
    std::cout << e.what() << "\n[line " << e.tok.get_line() << "]" << std::endl;
    had_runtime_error = true;
}

int lox::run(std::string code) {
    scanner scanner(std::move(code));
    auto tokens = scanner.scan_tokens();
    parser parser(tokens);
    auto statements = parser.parse();

    interp.interpret(statements);

    if (had_error) {
        std::cout << "Exiting due to error(s)";
        exit(65);
    }
    if (had_runtime_error) {
        exit(70);
    }
    return 0;
}
