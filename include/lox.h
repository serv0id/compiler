#ifndef COMPILER_LOX_H
#define COMPILER_LOX_H
#include <string>


class lox {
public:
    explicit lox(const std::string &file_name);
    std::string read_file() const;

    static void error(int line, const std::string &message);
    static void report(int line, const std::string &where, const std::string &message);

    int run(std::string code);
    static bool had_error;

private:
    std::string file;
};


#endif //COMPILER_LOX_H