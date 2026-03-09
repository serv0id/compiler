#include "parser.h"
#include "lox.h"
#include <algorithm>
#include <utility>

/*

expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;

*/

bool parser::is_at_end() {
    return peek().get_type() == EOFF;
}

token parser::peek() {
    return tokens.at(current);
}

token parser::previous() {
    return tokens.at(current - 1);
}

ParseError parser::error(const token& token, const std::string& message) {
    lox::error(token, message);
    return {};
}

token parser::advance() {
    if (!is_at_end()) current++;
    return previous();
}

bool parser::check(const TokenType type) {
    if (is_at_end()) return false;
    return peek().get_type() == type;
}

token parser::consume(const TokenType type, const std::string& message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}

bool parser::match(const std::vector<TokenType> &types) {
    for (const TokenType type: types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

std::unique_ptr<expr> parser::expression() {
    return equality();
}

std::unique_ptr<expr> parser::equality() {
    std::unique_ptr<expr> expression = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        token op = previous();
        std::unique_ptr<expr> right = comparison();
        expression = std::make_unique<binary>(std::move(expression), op, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::comparison() {
    std::unique_ptr<expr> expression = term();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        token op = previous();
        std::unique_ptr<expr> right = term();
        expression = std::make_unique<binary>(std::move(expression), op, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::term() {
    std::unique_ptr<expr> expression = factor();

    while (match({MINUS, PLUS})) {
        token op = previous();
        std::unique_ptr<expr> right = factor();
        expression = std::make_unique<binary>(std::move(expression), op, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::factor() {
    std::unique_ptr<expr> expression = p_unary();

    while (match({SLASH, STAR})) {
        token op = previous();
        std::unique_ptr<expr> right = p_unary();
        expression = std::make_unique<binary>(std::move(expression), op, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::p_unary() {
    if (match({BANG, MINUS})) {
        token op = previous();
        std::unique_ptr<expr> right = p_unary();
        return std::make_unique<unary>(op, std::move(right));
    }

    return primary();
}

std::unique_ptr<expr> parser::primary() {
    if (match({FALSE})) return std::make_unique<literal>(false);
    if (match({TRUE})) return std::make_unique<literal>(true);
    if (match({NIL})) return std::make_unique<literal>(nullptr);

    if (match({NUMBER, STRING})) return std::make_unique<literal>(previous().get_literal());

    if (match({LEFT_PAREN})) {
        std::unique_ptr<expr> expression = this->expression();
        consume(RIGHT_PAREN, "Expected ')' after expression.");
        return std::make_unique<grouping>(std::move(expression));
    }

    throw error(peek(), "Expected expression.");
}

void parser::synchronize() {
    advance();

    while (!is_at_end()) {
        if (previous().get_type() == SEMICOLON) return;
        switch (peek().get_type()) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
        }
        advance();
    }
}

std::unique_ptr<expr> parser::parse() {
    try {
        return expression();
    } catch (ParseError error) {
        return nullptr;
    }
}
