#include <utility>
#include "include/scanner.h"

#include "include/lox.h"
#include "include/token.h"

scanner::scanner(std::string source) {
    this->source = std::move(source);
}

bool scanner::is_at_end() {
    // checks if we reach the file end
    return current >= source.length();
}

std::vector<token> scanner::scan_tokens() {
    while (!is_at_end()) {
        // scan individual tokens
        start = current;
        scan_token();
    }

    tokens.emplace_back(EOFF, "", line, NULL); // add EOF at the end
    return tokens;
}

void scanner::scan_token() {
    // [actual lexer function]
    // we start by reading a single character and then matching
    // based on conditions
    switch (char c = source[current++]) {
        case '(': add_token(LEFT_PAREN); break;
        case ')': add_token(RIGHT_PAREN); break;
        case '{': add_token(LEFT_BRACE); break;
        case '}': add_token(RIGHT_BRACE); break;
        case ',': add_token(COMMA); break;
        case '.': add_token(DOT); break;
        case '-': add_token(MINUS); break;
        case '+': add_token(PLUS); break;
        case ';': add_token(SEMICOLON); break;
        case '*': add_token(STAR); break;

        case '!': add_token(match('=') ? BANG_EQUAL: BANG); break;
        case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
        case '>': add_token(match('=') ? GREATER_EQUAL: GREATER); break;

        case '/':
            if (match('/')) {
                while (!is_at_end() && source[current] != '\n') {
                    current++;
                }
            } else {
                add_token(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            line++;
            break;
        case '"': handle_string(); break;

        default: lox::error(line, "Unexpected character: " + std::to_string(c));
    }
}

void scanner::add_token(TokenType type) {
    add_token(type, NULL);
}

void scanner::add_token(TokenType type, std::any literal) {
    std::string text = source.substr(start,  current - start);
    tokens.emplace_back(type, text, line, literal);
}

bool scanner::match(const char c) {
    if (is_at_end()) return false;
    if (source[current++] != c) return false;
    current++;
    return true;
}

void scanner::handle_string() {
    while (!is_at_end() && source[current] != '"') {
        if (source[current] == '\n') line++;
        current++;
    }

    if (is_at_end()) {
        lox::error(line, "Unterminated string.");
        return;
    }

    current++;

    std::string value = source.substr(start + 1, current - start - 2);
    add_token(STRING, value);
}