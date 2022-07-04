#include "Stack.h"
#include "ComparableOp.h"

class Infix//中缀表达式,提供转为后缀表达式的方法
{
	public:
		Infix();
		Infix(const string& s);
		void set_infix_exp(const string& s);
		string ToPostfix();
	private:
		string infix_exp;
		string postfix_exp;
		Stack<ComparableOp> operator_stack;
		void CompareAndPop(const ComparableOp& op);
		bool IsOperator(char ch) const;
};