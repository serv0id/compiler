#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H
#include <vector>
#include "token.h"
#include "expr.h"


class parser {
    std::vector<token> tokens;
    int current = 0;

public:
    parser(std::vector<token> tokens) : tokens(std::move(tokens)) {};

    bool is_at_end();

    token peek();

    token previous();

    token advance();

    bool check(TokenType type);

    token consume(TokenType type, std::string message);

    bool match(const std::vector<TokenType> &);

    std::unique_ptr<expr> expression();

    std::unique_ptr<expr> equality();

    std::unique_ptr<expr> comparison();

    std::unique_ptr<expr> term();

    std::unique_ptr<expr> factor();

    std::unique_ptr<expr> p_unary();

    std::unique_ptr<expr> primary();
};


#endif //COMPILER_PARSER_H