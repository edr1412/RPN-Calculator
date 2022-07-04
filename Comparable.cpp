#include "ComparableOp.h"
ComparableOp::ComparableOp()
{}

ComparableOp::ComparableOp(char ch)
{	op = ch;    
	switch(op)
	{	case '+':   
		case '-':  
			inputPrecedence = 1;
			stackPrecedence = 1;	  
			break;
		case '*':   
		case '%':   
		case '/':  
			inputPrecedence = 2;
			stackPrecedence = 2;	  
			break;
		case '^':
			inputPrecedence = 4;
			stackPrecedence = 3;//右结合，新来的优先  
			break;
		case '(':  
			inputPrecedence = 5;
			stackPrecedence = -1;//进栈时最优先，但只有右括号才能使其出栈	  
			break;
		case ')':  
			inputPrecedence = 0;
			stackPrecedence = 0;	  
			break;
	}
}

char ComparableOp::getOp() const
{
	return op;
}

bool operator>= (const ComparableOp& left, const ComparableOp& right )
{
	return left.stackPrecedence >= right.inputPrecedence;
}