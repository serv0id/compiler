#include <utility>
#include "scanner.h"
#include <iostream>
#include <magic_enum/magic_enum.hpp>
#include "lox.h"
#include "token.h"

scanner::scanner(std::string source) {
    this->source = std::move(source);
}

const std::map<std::string, TokenType> scanner::keywords= {
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE}
};

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

    tokens.emplace_back(EOFF, "", line, std::any{}); // add EOF at the end
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

        default:
            if (isdigit(c)) {
                handle_number();
            } else if (isalpha(c) || c == '_') { // identifiers can start with an underscore
                handle_identifier();
            } else {
                lox::error(line, "Unexpected character: " + std::string(1, c));
            }
    }
}

void scanner::add_token(TokenType type) {
    add_token(type, std::any{});
}

void scanner::add_token(TokenType type, std::any literal) {
    std::string text = source.substr(start,  current - start);
    tokens.emplace_back(type, text, line, literal);
}

bool scanner::match(const char c) {
    if (is_at_end()) return false;
    if (source[current] != c) return false;
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

void scanner::handle_number() {
    while (!is_at_end() && isdigit(source[current])) {
        current++;
    }

    if (!is_at_end() && source[current] == '.') {
        if (current + 1 < source.length() && isdigit(source[current + 1])) {
            current++;
        }
        while (!is_at_end() && isdigit(source[current])) current++;
    }

    double value = std::stod(source.substr(start, current - start));
    add_token(NUMBER, value);
}

void scanner::handle_identifier() {
    while (!is_at_end() && (isalnum(source[current]) || source[current] == '_')) {
        current++;
    }

    std::string value = source.substr(start, current - start);

    if (auto it = keywords.find(value); it != keywords.end()) {
        add_token(it->second);
    } else add_token(IDENTIFIER, value);
}

void scanner::print_tokens() const {
    for (const auto& t : tokens) {
        std::cout << magic_enum::enum_name(t.get_type())
                  << " " << t.get_lexeme()
                  << " line=" << t.get_line()
                  << "\n";
    }
}
