#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"

class Expr
{
public:
    virtual ~Expr() = default;
};

using ExprPtr = std::shared_ptr<Expr>;

class numberExpr : public Expr
{
public:
    double value;

    numberExpr(double x)
    {
        value = x;
    }
};


class variableExpr :public Expr
{
public:
    std::string name;

    variableExpr(std::string NAme)
    {
        name = NAme;
    }
};


class BinaryExpr : public Expr
{
public:
    ExprPtr left;
    char op;
    ExprPtr right;

    BinaryExpr(ExprPtr l, char o, ExprPtr r)
    {
        left = l;
        op = o;
        right = r;
    }
};


class CallExpr :public Expr
{
public:
    std::string name;
    std::vector<ExprPtr> args;


    CallExpr(std::string n, std::vector<ExprPtr> a)
    {
        name = n;
        args = a;
    }
};

class Parser
{
public:

    Parser(std::vector<Token> tokenList)
    {
        tokens = tokenList;
        pos = 0;
    }

    ExprPtr parseExpr() 
    {
        ExprPtr leftSide = parseTerm();

        while (true)
        {
            Token currentToken = Peak();

            bool isPlus = (currentToken.type == TokenType::PLUS);
            bool isMinus = (currentToken.type == TokenType::MINUS);

            if (isPlus == false && isMinus == false)
            {
                break;
            }

            Token operatorToken = advance();
            char operatorChar = operatorToken.text[0];

            ExprPtr rightSide = parseTerm();

            leftSide = std::make_shared<BinaryExpr>(leftSide, operatorChar, rightSide);
        }

        return leftSide;
    
    }


private:
    std::vector<Token> tokens;
    int pos;

    Token Peak() 
    {
        return tokens[pos];
    }

    Token advance()
    {
        Token currentToken = tokens[pos];
        pos = pos + 1;
        return currentToken;
    }


    Token expect(TokenType exp) 
    {
        Token cToken = Peak();

        if (cToken.type != exp) 
        {
            throw "Erorr";
        }
        return advance();
    }

    ExprPtr parseTerm() 
    {
        ExprPtr lSide = parseFactor();

        while (true) 
        {
            Token cToken = Peak();

            if (!(cToken.type == TokenType::STAR) && !(cToken.type == TokenType::SLASH))
            {
                break;
            }

            Token operatorToken = advance();
            char operatorChar = operatorToken.text[0];


            ExprPtr rightSide = parseFactor();

            lSide = std::make_shared<BinaryExpr>(lSide, operatorChar, rightSide);
        }
        return lSide;
    }


    ExprPtr parseFactor() 
    {
        Token cToken = Peak();

        if (cToken.type == TokenType::NUMBER)
        {
            advance();
            return std::make_shared<numberExpr>(cToken.numValue);
        }


        if (cToken.type == TokenType::LPAREN)
        {
            advance();
            ExprPtr innerExpr = parseExpr();
            expect(TokenType::RPAREN);
            return innerExpr;
        }

        if (cToken.type == TokenType::IDENT)
        {
            advance();
            std::string identifierName = cToken.text;

            Token nextToken = Peak();
            bool nextIsLparen = (nextToken.type == TokenType::LPAREN);


            if (nextIsLparen == true) 
            {
                advance();

                std::vector<ExprPtr> argList;

                Token afterLparen = Peak();
                bool argsAreEmpty = (afterLparen.type == TokenType::RPAREN);

                if (argsAreEmpty == false)
                {
                    ExprPtr firstArgument = parseExpr();
                    argList.push_back(firstArgument);

                    while (true)
                    {
                        Token maybeComma = Peak();
                        bool isComma = (maybeComma.type == TokenType::COMMA);

                        if (isComma == false)
                        {
                            break;
                        }

                        advance();

                        ExprPtr nextArgument = parseExpr();
                        argList.push_back(nextArgument);
                    }
                }
                expect(TokenType::RPAREN);

                return std::make_shared<CallExpr>(identifierName, argList);
            
            }
            else 
            {
                return std::make_shared<variableExpr>(identifierName);
            }
        }


    }

};







