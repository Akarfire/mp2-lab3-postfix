#include "postfix.h"
#include "stack.h"

// Тесты с posftix.cpp работать не хотят, sample с реализацией в postfix.h не хочет работать, не знаю что с этим пока делать


/*
std::vector<MathObject*>& TPostfix::ToPostfix()
{
	TStack<MathFunction*> OperationStack(Infix.size());

	std::string CurrentString = Infix;

	MathObjectType PreviousType = NoType;

	int OpenBrackets = 0;

	while (CurrentString.size() > 0)
	{
		MathObject* MathObject;
		bool StackDump = false;

		if (AnalyzeNextLex(CurrentString, MathObject, StackDump, CurrentString))
		{
			OperationStack.size();
			// Handilg Stack Dump
			if (StackDump)
			{
				if (OpenBrackets == 0)
					throw(std::logic_error("Postfix Analysis: Invalid Syntaxis"));

				OpenBrackets--;

				while (!OperationStack.TopElem()->GetIsStackDumpBreaker())
					Postfix.push_back(OperationStack.Pop());

				if (!OperationStack.empty())
					Postfix.push_back(OperationStack.Pop());
			}

			// Handling types

			// If Operand
			else if (MathObject->GetType() == Operand)
			{
				Postfix.push_back(MathObject);
				PreviousType = Operand;
			}

			// If Operation
			else if (MathObject->GetType() == Operation)
			{

				MathFunction* Function = dynamic_cast<MathFunction*>(MathObject);
				if (Function)
				{
					if (PreviousType == Operation && !Function->GetIsStackDumpBreaker())
						throw(std::logic_error("Postfix Analysis: Invalid Syntaxis"));

					if (Function->GetIsStackDumpBreaker())
					{
						OperationStack.Push(Function);
						OpenBrackets++;
					}

					else
					{
						while (!OperationStack.empty() && Function->GetPriority() <= OperationStack.TopElem()->GetPriority())
							Postfix.push_back(OperationStack.Pop());

						OperationStack.Push(Function);
					}
				}

				else
					throw(std::logic_error("Postfix Analysis: Wrong math object type: marked as operation but ist a function"));

				PreviousType = Operation;
			}

			else
				throw(std::logic_error("Postfix Analysis: Tried processing math object of NoType"));
		}

		else
			throw(std::runtime_error("Postfix Analysis: Invalid Syntaxis"));
	}

	while (!OperationStack.empty())
		Postfix.push_back(OperationStack.Pop());

	return Postfix;
}

void TPostfix::ClearPostfix()
{
	for (auto p : DeletionList)
		delete p;
}

bool TPostfix::AnalyzeNextLex(std::string& OutString, MathObject*& OutMathObject, bool& OutStackDump, std::string CurrentString)
{
	std::string CurrentLex = "";
	int i = 0;

	OutStackDump = false;

	while (i < CurrentString.size())
	{
		if (CurrentString[i] == ' ')
		{
			i++;
			continue;
		}

		// RIGHT BRACKET
		if (CurrentString[i] == ')')
			if (CurrentLex.size() == 0)
			{
				OutString = CurrentString.substr(i + 1, CurrentString.size() - 1 - i);
				OutMathObject = nullptr;
				OutStackDump = true;

				return true;
			}

		// STACK DUMP BREAKERS
		if (CurrentString[i] == '(')
		{
			// if its just (
			if (CurrentLex.size() == 0)
			{
				LBracket* Obj;
				GetMathObjectPointer(Obj);

				OutMathObject = Obj;
				OutString = CurrentString.substr(i + 1, CurrentString.size() - 1 - i);

				return true;
			}

			// If its a breaker funcion (functions like a '(' but has a mathematical operation)
			if (CurrentLex == "sin")
			{
				Sin* Obj;
				GetMathObjectPointer(Obj);

				OutMathObject = Obj;
				OutString = CurrentString.substr(i + 1, CurrentString.size() - 1 - i);

				return true;
			}

			else if (CurrentLex == "cos")
			{
				Cos* Obj;
				GetMathObjectPointer(Obj);

				OutMathObject = Obj;
				OutString = CurrentString.substr(i + 1, CurrentString.size() - 1 - i);

				return true;
			}

			// No Suitable function found, interprete as "a * (" if possible ('a' is a varibale or a const)

			else if (IsValidNumber(CurrentLex))
			{
				OutMathObject = new Constant(std::stod(CurrentLex));
				DeletionList.push_back(OutMathObject);
				OutString = '*' + CurrentString.substr(i, CurrentString.size() - i);

				return true;
			}

			else if (IsValidVariableName(CurrentLex))
			{
				OutMathObject = new UserVariable(CurrentLex);
				DeletionList.push_back(OutMathObject);
				OutString = '*' + CurrentString.substr(i, CurrentString.size() - i);

				return true;
			}

			// Invalid syntaxis then
			else
			{
				OutString = CurrentString;
				OutMathObject = nullptr;

				return false;
			}
		}

		// OPERATORS and INLINE VALUES
		if (std::string(")+*-/").find(CurrentString[i]) != std::string::npos)
		{
			// If its the first simbol encountered, then its just an operator
			// OPERATORS
			if (CurrentLex.size() == 0)
			{
				if (CurrentString[i] == '+')
				{
					Add* Obj;
					GetMathObjectPointer(Obj);

					OutMathObject = Obj;
					OutString = CurrentString.substr(1 + i, CurrentString.size() - 1 - i);

					return true;
				}

				if (CurrentString[i] == '-')
				{
					Subtract* Obj;
					GetMathObjectPointer(Obj);

					OutMathObject = Obj;
					OutString = CurrentString.substr(1 + i, CurrentString.size() - 1 - i);

					return true;
				}

				if (CurrentString[i] == '*')
				{
					Multiply* Obj;
					GetMathObjectPointer(Obj);

					OutMathObject = Obj;
					OutString = CurrentString.substr(1 + i, CurrentString.size() - 1 - i);

					return true;
				}

				if (CurrentString[i] == '/')
				{
					Divide* Obj;
					GetMathObjectPointer(Obj);

					OutMathObject = Obj;
					OutString = CurrentString.substr(1 + i, CurrentString.size() - 1 - i);

					return true;
				}
			}

			// Otherwise, its the end of the current lexem 
			// Finish lexem analysis
			// VALUES
			else if (IsValidNumber(CurrentLex))
			{
				OutMathObject = new Constant(std::stod(CurrentLex));
				DeletionList.push_back(OutMathObject);
				OutString = CurrentString.substr(i, CurrentString.size() - i);

				return true;
			}

			else if (IsValidVariableName(CurrentLex))
			{
				OutMathObject = new UserVariable(CurrentLex);
				DeletionList.push_back(OutMathObject);
				OutString = CurrentString.substr(i, CurrentString.size() - i);

				return true;
			}

			// Invalid syntaxis then
			else
			{
				OutString = CurrentString;
				OutMathObject = nullptr;

				return false;
			}
		}

		// Registering last operand
		// ENDING VALUES
		if (i == CurrentString.size() - 1)
		{
			CurrentLex += CurrentString[i];

			if (IsValidNumber(CurrentLex))
			{
				OutMathObject = new Constant(std::stod(CurrentLex));
				DeletionList.push_back(OutMathObject);
				OutString = "";

				return true;
			}

			else if (IsValidVariableName(CurrentLex))
			{
				OutMathObject = new UserVariable(CurrentLex);
				DeletionList.push_back(OutMathObject);
				OutString = "";

				return true;
			}

			// Invalid syntaxis then
			else
			{
				OutString = CurrentString;
				OutMathObject = nullptr;

				return false;
			}
		}
			
			
		CurrentLex += CurrentString[i];
		i++;
	}

	return false;
}

bool TPostfix::IsValidNumber(std::string& InString)
{
	for (char c : InString)
		if (std::string("1234567890.,").find(c) == std::string::npos)
			return false;

	double Number = 0;

	try
	{
		Number = std::stod(InString);
	}

	catch(std::invalid_argument exception) { return false; }
	return true;
}

bool TPostfix::IsValidVariableName(std::string& InString)
{
	for (char c : InString)
		if (std::string("QWERTYUIOPASDFGHJKLLZXCVBNMqwertyuiiopasdfghjkllzxcvbnm_").find(c) == std::string::npos)
			return false;

	return true;
}

double TPostfix::Calculate(std::map<std::string, double> UserVariables)
{
	if (Postfix.size() == 0)
		throw(std::runtime_error("Postfix Calculation: Empty postfix calculation is not allowed!"));

	TStack<double> CalculationStack(Postfix.size());

	for (size_t i = 0; i < Postfix.size(); i++)
	{
		CalculationStack.Push(Postfix[i]->GetValue(UserVariables, CalculationStack));
	}

	return CalculationStack.Pop();
}
*/