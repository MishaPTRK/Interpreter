#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

class Lexer
{
public:
    int pos = 0;
    std::string str;

    Lexer(std::string inputText)
    {
        str = inputText;
        pos = 0;
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        while ((int)str.size() > pos)
        {
            char c = str[pos];

            if (std::isspace(c))
            {
                pos++;
                continue;
            }
            if (std::isdigit(c))
            {
                tokens.push_back(readNumber());
                continue;
            }


            if (std::isalpha(c) || c == '_')
            {
                tokens.push_back(readIdentifier());
                continue;
            }


            switch (c)

            {
            case '+':
                tokens.push_back({ TokenType::PLUS, "+" });
                pos++;
                break;
            case '-':
                tokens.push_back({ TokenType::MINUS, "-" });
                pos++;
                break;
            case '*':
                tokens.push_back({ TokenType::STAR, "*" });
                pos++;
                break;
            case '/':
                tokens.push_back({ TokenType::SLASH, "/" });
                pos++;
                break;
            case '=':
                tokens.push_back({ TokenType::ASSIGN, "=" });
                pos++;
                break;
            case '(':
                tokens.push_back({ TokenType::LPAREN, "(" });
                pos++;
                break;
            case ')':
                tokens.push_back({ TokenType::RPAREN, ")" });
                pos++;
                break;
            case '{':
                tokens.push_back({ TokenType::LBRACE, "{" });
                pos++;
                break;
            case '}':
                tokens.push_back({ TokenType::RBRACE, "}" });
                pos++;
                break;
            case ',':
                tokens.push_back({ TokenType::COMMA, "," });
                pos++;
                break;
            default:
                throw std::runtime_error(std::string("Newidomiy symvol: ") + c);
            }
        }
        tokens.push_back({ TokenType::END_OF_LINE, "" });
        return tokens;
    }

private:

    Token readNumber()
    {
        int startPosition = pos;
        bool dotAlreadyFound = false;

        while (pos < (int)str.size()) {
            char currentChar = str[pos];

            bool isDigit = std::isdigit(currentChar);
            bool isFirstDot = (currentChar == '.' && dotAlreadyFound == false);

            if (isDigit == false && isFirstDot == false)
            {
                break;
            }

            if (currentChar == '.')
            {
                dotAlreadyFound = true;
            }

            pos = pos + 1;
        }

        int length = pos - startPosition;
        std::string numberText = str.substr(startPosition, length);

        Token result;
        result.type = TokenType::NUMBER;
        result.text = numberText;
        double numvalue = std::stod(numberText);
        result.numValue = numvalue;

        return result;
    }


    Token readIdentifier()
    {
        int startPos = pos;

        while (pos < (int)str.size())
        {
            char currentChar = str[pos];

            bool isLetter = std::isalpha(currentChar);
            bool isDigit = std::isdigit(currentChar);

            bool isUnderscore = (currentChar == '_');

            if (isLetter == false && isDigit == false && isUnderscore == false) {
                break;
            }

            pos = pos + 1;
        }


        int length = pos - startPos;
        std::string word = str.substr(startPos, length);

        Token result;
        result.text = word;
        result.numValue = 0;
        if (word == "var") {
            result.type = TokenType::VAR;
        }
        else if (word == "def") {
            result.type = TokenType::DEF;
        }
        else {
            result.type = TokenType::IDENT;
        }
        return result;
    }
};