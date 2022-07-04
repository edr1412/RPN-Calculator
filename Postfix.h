#include "Stack.h"
#include <math.h>


class Postfix//后缀表达式，提供计算方法
{
	public:
		Postfix();
        Postfix(const string& s);
		void set_postfix_exp(const string&  s);
		double Calculate();
	private:
		string postfix_exp;
		Stack<double> operand_stack;
		void GetOperands(double& left, double& right);
		double Compute(double left, double right, char op) const;
		bool IsOperator(char ch) const;
};

