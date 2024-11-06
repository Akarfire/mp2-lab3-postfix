#include "MathObjects.h"
#include <cmath>

// Utility
// A breaker function, but does nothing
class LBracket final : public MathFunction
{
public:
	LBracket() : MathFunction() 
	{
		StackDumpBreaker = true;
		Priority = 0;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		return CalculationStack.Pop();
	}
};

// Math Functions
class Add final : public MathFunction
{
public:
	Add() : MathFunction() 
	{
		Priority = 1;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		double Value_1 = CalculationStack.Pop();
		return CalculationStack.Pop() + Value_1;
	}
};

class Subtract final : public MathFunction
{
public:
	Subtract() : MathFunction()
	{
		Priority = 1;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		double Value_1 = CalculationStack.Pop();
		return CalculationStack.Pop() - Value_1;
	}
};

class Multiply final : public MathFunction
{
public:
	Multiply() : MathFunction()
	{
		Priority = 2;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		double Value_1 = CalculationStack.Pop();
		return CalculationStack.Pop() * Value_1;
	}
};

class Divide final : public MathFunction
{
public:
	Divide() : MathFunction()
	{
		Priority = 2;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		double Value_1 = CalculationStack.Pop();
		return CalculationStack.Pop() / Value_1;
	}
};

// Breaker functions
// Act as if they are 'f(...)'
class Sin final : public MathFunction
{
public:
	Sin() : MathFunction()
	{
		StackDumpBreaker = true;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		return sin(CalculationStack.Pop());
	}
};

class Cos final : public MathFunction
{
public:
	Cos() : MathFunction()
	{
		StackDumpBreaker = true;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		return cos(CalculationStack.Pop());
	}
};