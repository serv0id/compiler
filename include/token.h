#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H
#include <any>
#include <string>
#include "tokentype.h"


class token {
public:
    token(TokenType type,
             std::string lexeme,
             int line,
             std::any  literal);

    TokenType get_type() const { return type; }
    const std::string& get_lexeme() const { return lexeme; }
    int get_line() const { return line; }
    const std::any& get_literal() const { return literal; }

private:
    const TokenType type;
    const std::string lexeme;
    const int line;
    const std::any literal;
};


#endif //COMPILER_TOKEN_H