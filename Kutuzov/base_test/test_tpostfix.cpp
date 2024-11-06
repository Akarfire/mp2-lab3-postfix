#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p("a + b"));
}

TEST(TPostfix, can_calculate_simple_expressions)
{
	TPostfix p("a + b - c * d / a");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"a", 10},
		{"b", 5},
		{"c", 3},
		{"d", 2.5}
	};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(14.25, OutValue);
}

TEST(TPostfix, can_calculate_expressions_with_brackets)
{
	TPostfix p("a + (b - c) * d / (a - b)");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"a", 10},
		{"b", 5},
		{"c", 3},
		{"d", 2.5}
	};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(11, OutValue);
}

TEST(TPostfix, can_calculate_expressions_with_constants)
{
	TPostfix p("2 * (56.78 - 3) + 10 / (3 + 2)");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(109.56, OutValue);
}

TEST(TPostfix, can_calculate_expressions_with_long_var_names)
{
	TPostfix p("longname + veryloooooooooongname / small");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"longname", 105.3},
		{"veryloooooooooongname", 15.5},
		{"small", 5}
	};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(108.4, OutValue);
}

TEST(TPostfix, can_calculate_multiplication_by_bracket_without_sign)
{
	TPostfix p("a + b(a + c)");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"a", 5},
		{"b", 3},
		{"c", 2}
	};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(26, OutValue);
}

TEST(TPostfix, can_calculate_sin_function)
{
	TPostfix p("a + 2 * sin(b + (d - a) / d) + a");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"a", 5},
		{"b", 3},
		{"c", 2},
		{"d", 10}
	};

	double OutValue = 0;
	ASSERT_NO_THROW(OutValue = p.Calculate(Args));

	EXPECT_FLOAT_EQ(9.29843354462, OutValue);
}

TEST(TPostfix, throws_when_empty_operation_full_empty)
{
	TPostfix p("");

	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_wrong_brackets)
{
	TPostfix p("k * a + d)");

	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_wrong_operations)
{
	TPostfix p("k ++ d");

	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_invalid_variable_name)
{
	TPostfix p("a + k~$%$#");

	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_doesnt_receive_variable)
{
	TPostfix p("a + 2 * sin(b + (d - a) / d) + a");

	ASSERT_NO_THROW(p.ToPostfix());

	std::map<std::string, double> Args = {
		{"a", 5},
		{"b", 3},
		{"c", 2},
	};

	double OutValue = 0;
	ASSERT_ANY_THROW(OutValue = p.Calculate(Args));
}

