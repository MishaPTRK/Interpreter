
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Environment.h"

int main()
{
    Environment env;
    Evaluator evaluator;
    std::string inputLine;


    while (true) 
    {
        std::getline(std::cin, inputLine);

        if (inputLine == "exit" || inputLine == "quit")
        {
            break;
        }

        if (inputLine.empty())
        {
            continue;
        }

        Lexer lexer(inputLine);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        StatementPtr stmt = parser.parseStatement();

        double result = 0;

        if (evaluator.execute(stmt, env, result) == true)
        {
            std::cout << result << std::endl;
        }
    
    }
    return 0;

}