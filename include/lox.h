#ifndef COMPILER_LOX_H
#define COMPILER_LOX_H
#include <string>
#include "interpreter.h"
#include "runtimeerror.h"
#include "token.h"


class lox {
public:
    explicit lox(const std::string &file_name);
    std::string read_file() const;

    static void error(const token& token, const std::string& string);
    static void error(int line, const std::string &message);
    static void report(int line, const std::string &where, const std::string &message);
    static void runtime_error(RuntimeError e);

    int run(std::string code);
    static bool had_error;
    static bool had_runtime_error;
    static interpreter interp;

private:
    std::string file;
};


#endif //COMPILER_LOX_H