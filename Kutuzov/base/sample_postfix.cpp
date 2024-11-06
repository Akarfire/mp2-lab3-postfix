#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	TPostfix postfix("");
	double res;

	//setlocale(LC_ALL, "Russian");
	//cout << "Введите арифметическое выражение: ";
	//cin >> expression;
	//cout << expression << endl;
	std::cout << "Math Expression: " << postfix.GetInfix() << endl;
	try
	{
		postfix.ToPostfix();
		//cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
		std::map<std::string, double> Args = {
		{"a", 5},
		{"b", 3},
		{"c", 2},
		{"d", 10}
		};

		res = postfix.Calculate(Args);
		std::cout << res << endl;
	}

	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
