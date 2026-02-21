#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H
#include <map>
#include <string>
#include <vector>
#include "token.h"


class scanner {
public:
    scanner(std::string source);

    bool is_at_end();

    std::vector<token> scan_tokens();

    void scan_token();

    void add_token(TokenType type);

    void add_token(TokenType type, std::any literal);

    bool match(char c);

    void handle_string();

    void handle_number();

    void handle_identifier();

private:
    std::vector<token> tokens;
    static const std::map<std::string, TokenType> keywords;
    std::string source;
    int start = 0;
    int line = 1;
    int current = 0;
};


#endif //COMPILER_SCANNER_H