#include "Infix.h"
void Infix::CompareAndPop(const ComparableOp& op)//依次将栈内优先度比op更高或相等的运算符出栈
{
	ComparableOp op2;
	while(!operator_stack.empty() && (op2 = operator_stack.top()) >= op)
	{
        cout<<"└──Pop:"<<op2.getOp()<<endl;
        operator_stack.pop();
		postfix_exp += op2.getOp();
        cout<<"└──Add:"<<op2.getOp()<<endl;
		postfix_exp += ' ';
        cout<<"└──Add:<SPACE>\n";
	}
}

bool Infix::IsOperator(char ch) const// 检查ch是否为'+','-','*','/','%','^'其中一个
{
	return ch == '+' || ch == '-' || ch == '*' ||
		ch == '%' || ch == '/' || ch == '^';
}

Infix::Infix()
{}

Infix::Infix(const string& s):
	infix_exp(s)
{}

void Infix::set_infix_exp(const string& s)//获取中缀表达式
{
	infix_exp = s;
}

string Infix::ToPostfix()//转为后缀表达式的主要函数
{
	ComparableOp op;
	int i,flag=0;//flag最低位至高位分别表示有无小数点，有无合法数字，有无数字后空格
	int last_is_bracket=1;//根据之前是否是括号，可判断是否需要加空格，以及负号是否有效。初始设为1，则可以在首位使用负号
	char ch;
	try
	{
		for (i=0; i < infix_exp.length(); i++)
		{
			ch = infix_exp[i];
			cout<<i<<"\tch:"<<ch<<"\tString:"<<postfix_exp<<endl;
			if (isdigit(ch)||ch=='.')
			{
				last_is_bracket=0;
				postfix_exp += ch;
				cout<<"└──Add:"<<ch<<endl;
				if(flag>=4){//刚出现过空格，再出现数字就说明式子有问题
					throw "Infix to Postfix: Operator expected";
				}
				if(ch=='.'){
					if(flag!=2)
						throw "Infix to Postfix: Invalid dot";
					flag^=2;//去除低第2位
					flag|=1;//最低位置1
				}
				if(isdigit(ch))
					flag|=2;//低第2位置1
				
			}
			else if(isspace(ch)){
				if(flag>0)
					flag|=4;//标记数字后出现空格
			}
			else if (IsOperator(ch))
			{
				if(ch=='-' && last_is_bracket==1){//处理负号情况,视为0-
					postfix_exp += "0 ";
					cout<<"└──Add:0\n";
					cout<<"└──Add:<SPACE>\n";
					last_is_bracket=3;//标记已有负号
				}
				else if(ch=='-' && last_is_bracket==3){//连续负号，视为0+
					postfix_exp += "0 ";
					cout<<"└──Add:0\n";
					cout<<"└──Add:<SPACE>\n";
					ch='+';//中和之前的减号
					last_is_bracket=1;//复原
				}
				else{
					if(int(flag&2)==0)//若是运算符则检查前面是否有数字。这里必须用int
						throw "Infix to Postfix: Operand expected";
					if(last_is_bracket == 0){
						postfix_exp += ' ';//添加数字后的空格
						cout<<"└──Add:<SPACE1>\n";
					}
				}
				op = ComparableOp(ch);
				CompareAndPop(op);//取出优先级更高或相等的运算符
				operator_stack.push(op);//入栈
				cout<<"└──Push:"<<op.getOp()<<endl;
				flag=0;
			}
			else if (ch == '('){
				if(flag != 0)
					throw "Infix to Postfix: Operator expected";//左括号前必须不是数字
				last_is_bracket=1;
				op = ComparableOp(ch);
				operator_stack.push(op);//入栈
				cout<<"└──Push:("<<endl;
				flag=0;
			}
			else if (ch == ')')
			{
				if(int(flag&2)==0)
					throw "Infix to Postfix: Operand expected";
				flag|=4;//像空格一样有间隔开数字
				postfix_exp += ' ';//添加数字后的空格
				cout<<"└──Add:<SPACE2>\n";
				last_is_bracket=2;//告诉上一个if已经添加过空格
				op = ComparableOp(ch);
				CompareAndPop(op);//除了左括号的运算符都将出栈
				if(operator_stack.empty())
					throw "Infix to Postfix: Missing '('";//没有左括号与之配对
				else{//左括号出栈
					cout<<"└──Pop:"<<operator_stack.top().getOp()<<endl;
					operator_stack.pop(); 
				}
			}
			else//其他非法字符
				throw "Infix to Postfix: Invalid input";
		}
		if (int(flag&2)==0)
			throw "Infix to Postfix: Operand expected";
		else//导出剩余符号
		{   
			postfix_exp += ' ';
			cout<<"└──Add:<SPACE>\n";
			while (!operator_stack.empty())
			{
				op = operator_stack.top();
				cout<<"└──Pop:"<<op.getOp()<<endl;
				operator_stack.pop();
				if (op.getOp() == '(')//检查是否存在未配对的左括号
					throw "Infix to Postfix: Missing ')'";
				else
				{
					postfix_exp += op.getOp();
					cout<<"└──Add:"<<op.getOp()<<endl;
					postfix_exp += ' ';
					cout<<"└──Add:<SPACE>\n";
				}
			}
			postfix_exp = postfix_exp.substr(0, postfix_exp.length() - 1);//去除最后的一个空格
			cout<<"└──Del:<SPACE>\n";
		}
	}catch(const char* msg){
        cerr<<msg<<endl;//输出异常信息
        exit(1);
    }
	return postfix_exp;
}
