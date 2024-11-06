#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	TPostfix postfix("a + 5*big(10 + 7.3) / (a + big) * 10");
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
		std::map<std::string, double> Args = { {"a", 100}, {"big", 2.15} };

		res = postfix.Calculate(Args);
		std::cout << res << endl;
	}

	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
