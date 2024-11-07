#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.h"
#include "MathFunctions.h"


class TPostfix
{
	std::string Infix;
	std::vector<MathObject*> Postfix;

	std::map<std::string, MathObject*> MathObjectBuffer;

	std::vector<MathObject*> DeletionList;

public:
	TPostfix(const std::string& InInfix): Infix(InInfix) {};
	~TPostfix() { ClearPostfix(); }

	std::string GetInfix() { return Infix; }
	std::vector<MathObject*> GetPostfix() { return Postfix; }

	std::vector<MathObject*>& ToPostfix();

	bool AnalyzeNextLex(std::string& OutString, MathObject*& OutMathObject, bool& OutStackDump, std::string CurrentString);
	bool IsValidNumber(std::string& InString);
	bool IsValidVariableName(std::string& InString);

	std::vector<std::string> GetVariableNames();
	double Calculate(std::map<std::string, double> UserVariables); // Ввод переменных, вычисление по постфиксной форме

	// Data Management
	void ClearPostfix();

	template<typename T> 
	void GetMathFunctionPointer(T*& OutPointer, const std::string& InFunctionName)
	{
		if (MathObjectBuffer.count(InFunctionName) > 0)
		{
			T* OutFunction = dynamic_cast<T*>(MathObjectBuffer[InFunctionName]);
			if (OutFunction)
				OutPointer = OutFunction;

			else
				throw("Data Management: wrong type name / buffer corruption");
		}

		else
		{
			OutPointer = new T();
			DeletionList.push_back(OutPointer);
			MathObjectBuffer[InFunctionName] = OutPointer;
		}
	}

	MathObject* GetUserVariablePointer(const std::string& InVarName)
	{
		if (MathObjectBuffer.count("var_" + InVarName) > 0)
			return MathObjectBuffer["var_" + InVarName];

		MathObject* Var = new UserVariable(InVarName);
		DeletionList.push_back(Var);
		MathObjectBuffer["var_" + InVarName] = Var;
		return Var;
	}

	MathObject* GetConstantPointer(const double Value, const std::string& InConstLexem)
	{
		if (MathObjectBuffer.count(InConstLexem) > 0)
			return MathObjectBuffer[InConstLexem];

		MathObject* Const = new Constant(Value);
		DeletionList.push_back(Const);
		MathObjectBuffer[InConstLexem] = Const;
		return Const;
	}

};

#endif