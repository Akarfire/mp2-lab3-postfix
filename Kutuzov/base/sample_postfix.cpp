#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	std::cout << "Postfix Sample Program" << std::endl << "+, -, *, /, sin, cos; No numbers in variable names" << std::endl;

	bool Running = true;
	while (Running)
	{
		std::string Expression;

		std::cout << "Enter Your Math Expression ('end' to exit): ";
		std::getline(std::cin, Expression);

		if (Expression == "end")
			break;

		TPostfix Postfix(Expression);

		std::vector<std::string> Variables;
		std::map<std::string, double> Args = {};

		double Result;
		
		try
		{
			Postfix.ToPostfix();
			//cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

		}
		catch (std::exception& e)
		{
			std::cout << std::endl << "!CONVERSION ERROR!: " << std::endl << e.what() << std::endl;
			continue;
		}

		Variables = Postfix.GetVariableNames();

		for (auto var : Variables)
		{
			bool ValidValue = true;
			double OutValue = 0.0;

			do
			{
				std::cout << "Enter '" << var << "'" << " value: ";
				std::string rec;
				std::cin >> rec;

				if (cin.fail())
					cin.clear();

				cin.ignore(INT_MAX, '\n');

				ValidValue = true;
				try
				{
					OutValue = std::stod(rec);
				}
				catch (std::invalid_argument exception)
				{
					ValidValue = false;
					std::cout << std::endl << "Invalid value, please try again!" << std::endl;
				}


			} while (!ValidValue);

			Args[var] = OutValue;
		}

		try
		{
			Result = Postfix.Calculate(Args);
		}
		catch (std::exception& e)
		{
			std::cout << std::endl << "!CALCULATION ERROR!: " << std::endl << e.what() << std::endl;
			continue;
		}

		std::cout << std::endl << "Result: " << Result << std::endl;
	}

	return 0;
}
