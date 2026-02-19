#include "token.h"

token::token(const TokenType type,
         std::string lexeme,
         const int line,
         const std::any& value)
: type(type),
  lexeme(std::move(lexeme)),
  line(line),
  literal(value)
{}

