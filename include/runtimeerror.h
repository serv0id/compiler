#ifndef COMPILER_RUNTIMEERROR_H
#define COMPILER_RUNTIMEERROR_H
#include <stdexcept>
#include <utility>
#include "token.h"

class RuntimeError : public std::runtime_error {
public:
    token tok;

    RuntimeError(token tok, const std::string& message)
        : std::runtime_error(message), tok(std::move(tok)) {}
};


#endif //COMPILER_RUNTIMEERROR_H