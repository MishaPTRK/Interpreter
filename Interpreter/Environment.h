#pragma once
#include <string>
#include <map>
#include "Parser.h"
#include <cmath>
#include <algorithm>

class Environment
{
public:

	std::map<std::string, double> variables;

	void AddValue(std::string name, double value)
	{

		if ((variables.find(name) != variables.end()) == true)
		{
			throw "Eror";
		}

		variables[name] = value;

	}


	double Get(std::string name)
	{
		auto it = variables.find(name);

		bool found = (it != variables.end());
		if (!found)
		{
			throw "Eror";
		}

		return it->second;
	}
};



class Evaluator
{
public:



	double eval(ExprPtr node, Environment& env)
	{
		if (auto asNumber = std::dynamic_pointer_cast<numberExpr>(node))
		{
			return asNumber->value;
		}

		if (auto asVar = std::dynamic_pointer_cast<variableExpr>(node))
		{
			return env.Get(asVar->name);
		}

		auto asBinary = std::dynamic_pointer_cast<BinaryExpr>(node);
		if (asBinary != nullptr)
		{
			double leftValue = eval(asBinary->left, env);
			double rightValue = eval(asBinary->right, env);

			if (asBinary->op == '+')
			{
				return leftValue + rightValue;
			}
			if (asBinary->op == '-')
			{
				return leftValue - rightValue;
			}
			if (asBinary->op == '*')
			{
				return leftValue * rightValue;
			}
			if (asBinary->op == '/')
			{
				if (rightValue == 0)
				{
					throw "Eror";
				}
				return leftValue / rightValue;
			}
			throw "Newidomiy Symvol";
		}



		auto asCall = std::dynamic_pointer_cast<CallExpr>(node);


		if (std::dynamic_pointer_cast<CallExpr>(node) != nullptr)
		{
			std::vector<double> argValues;
			for (int i = 0; i < (int)asCall->args.size(); i++)
			{
				double argResult = eval(asCall->args[i], env);
				argValues.push_back(argResult);
			}

			if (asCall->name == "max")
			{
				return std::max(argValues[0], argValues[1]);
			}


			if (asCall->name == "min")
			{
				return std::min(argValues[0], argValues[1]);
			}
			if (asCall->name == "abs")
			{
				return std::abs(argValues[0]);
			}
			if (asCall->name == "pow")
			{
				return std::pow(argValues[0], argValues[1]);
			}

			throw "Newidomiy symvol: ";
		}

		throw "Newidomiy type";

	}


	bool execute(StatementPtr stmt, Environment& env, double& outResult)
	{
		auto asVarStmt = std::dynamic_pointer_cast<VarStatement>(stmt);
		if (asVarStmt != nullptr)
		{
			double value = eval(asVarStmt->expression, env);
			env.AddValue(asVarStmt->name, value);
			return false;
		}

		auto asExprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt);
		if (asExprStmt != nullptr)
		{
			outResult = eval(asExprStmt->expression, env);
			return true;
		}

		throw "Type newidomiy";
	}
};
