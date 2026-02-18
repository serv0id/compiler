#ifndef COMPILER_LOX_H
#define COMPILER_LOX_H
#include <fstream>
#include <string>


class lox {
public:
    explicit lox(const std::string &file_name);
    int run(std::string code);

    std::string read_file() const;

private:
    std::string file;
};


#endif //COMPILER_LOX_H