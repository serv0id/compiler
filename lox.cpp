#include "lox.h"
#include <fstream>

lox::lox(const std::string &file_name) {
    file = file_name;
}

std::string lox::read_file() const {
    std::ifstream filestream(this->file, std::ios::binary);
    std::string file_contents{std::istreambuf_iterator<char>(filestream),
                              std::istreambuf_iterator<char>()};

    return file_contents;
}
