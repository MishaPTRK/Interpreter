#pragma once
#include <string>
enum class TokenType
{
	NUMBER, IDENT, VAR, DEF, PLUS, MINUS, STAR, SLASH, ASSIGN,LPAREN, RPAREN, LBRACE, RBRACE, COMMA, END_OF_LINE
};
struct Token
{
    TokenType type;
    std::string text;
    double numValue = 0;
};