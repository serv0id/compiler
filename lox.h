#ifndef COMPILER_LOX_H
#define COMPILER_LOX_H
#include <fstream>
#include <string>


class lox {
public:
    explicit lox(const std::string &file_name);
    std::string read_file() const;

    void error(const int &line, const std::string &message);
    void report(const int &line, const std::string &where, const std::string &message);

    int run(std::string code);

private:
    std::string file;
    bool had_error = false;
};


#endif //COMPILER_LOX_H