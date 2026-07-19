
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Expr
{
public:
    virtual ~Expr() = default;
};

using ExprPtr= std::shared_ptr<Expr>;

class numberExpr : public Expr
{
public:
    double value;

    numberExpr(double x) 
    {
        value = x;
    }
};


class variableExpr:public Expr
{
public:
    std::string name;

    variableExpr(std::string NAme) 
    {
        name = NAme;
    }
};


class BinaryExpr  : public Expr
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
    std::vector<Token> tokens;
    Parser(std::vector<Token> tokenList) 
    {
        tokens = tokenList;
        pos = 0;
    }





};







