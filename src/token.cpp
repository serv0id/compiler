#include "../include/token.h"
#include <utility>

token::token(const TokenType type,
         std::string lexeme,
         const int line,
         std::any  literal)
: type(type),
  lexeme(std::move(lexeme)),
  line(line),
  literal(std::move(literal))
{}



