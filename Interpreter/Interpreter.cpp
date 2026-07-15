
#include <iostream>
#include <vector>

enum class TokenType {NUMBER,IDENT,VAR, DEF,PLUS, MINUS, STAR, SLASH, ASSIGN,
    LPAREN, RPAREN, LBRACE, RBRACE,COMMA,END_OF_LINE};


struct Token {
    TokenType type;
    std::string text; 
    double numValue = 0;


class Lexer {
public:
    int pos = 0;
    std::vector<Token> tokens;
    
};


int main()
{

    std::cout << "Hello World!\n";
}

