#include <string>
#include <stdexcept>


enum MathObjectType {NoType, Operand, Operation};

// Abstract Classes

class MathObject
{
protected:
	MathObjectType Type;
	std::string Name;

public:
	MathObject()
	{
		Type = NoType;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) = 0;
	MathObjectType& GetType() { return Type; }
};

class MathFunction : public MathObject
{
protected:
	bool StackDumpBreaker;
	int Priority;

public:
	MathFunction() : MathObject() 
	{
		Type = Operation;
		StackDumpBreaker = false;
		Priority = 0;
	}
	
	bool GetIsStackDumpBreaker() { return StackDumpBreaker; }
	int GetPriority() { return Priority; }
};

//----------------------
// Final Classes

class Constant final: public MathObject
{
	double Value;

public:
	Constant(const double InConst): MathObject(), Value(InConst)
	{
		Type = Operand;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override { return Value; }
};

class UserVariable final : public MathObject
{
	std::string VarName;

public:
	UserVariable(const std::string& InVarName): MathObject(), VarName(InVarName)
	{
		Type = Operand;
	}

	virtual double GetValue(std::map<std::string, double>& UserVariables, TStack<double>& CalculationStack) override
	{
		if (UserVariables.count(VarName) > 0)
			return UserVariables[VarName];

		else
			throw std::runtime_error("No Such User Variable: " + VarName);
	}

	const std::string& GetVarName() { return VarName; }
};

