
#include <iostream>
#include <vector>
#include <string>

int main()
{
    Lexer lexer("var a = max(3, 2)");
    std::vector<Token> tkns= lexer.tokenize();
    for (Token& t : tkns) {
        std::cout << t.text << std::endl;
    }
    return 0;

}