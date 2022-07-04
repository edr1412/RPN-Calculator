#include "Postfix.h"
void Postfix::GetOperands(double& left, double& right)
{
	if (operand_stack.empty())
		throw  "Posifix Calculate: Too many operators";
	right = operand_stack.top();//先弹出到right，因为左边的先进栈
    cout<<"└──Pop:"<<right<<endl;
	operand_stack.pop();
	if (operand_stack.empty())
		throw "Posifix Calculate: Too many operators";
	left = operand_stack.top();
    cout<<"└──Pop:"<<left<<endl;
	operand_stack.pop();
}
double Postfix::Compute(double left, double right, char op) const//实现两个数的运算
{
	double value;
	switch(op)
	{	case '+':	
            value = left + right;	
            break;
		case '-':	
            value = left - right;	
            break;
		case '*':	
            value = left * right;	
            break;
		case '%':	
            if (right == 0)						     
                throw "Posifix Calculate: divide by 0";
			value = fmod(left,right);//用fmod可实现double类型的取余运算		
            break;
		case '/':	
            if (right == 0)
				throw "Posifix Calculate: divide by 0";
			value = left / right;		
            break;
		case '^':	
            if (left == 0 && right == 0)
				throw "Posifix Calculate: 0^0 undefined";
			value = pow(left,right);
            break;
	}
	return value;	
}
bool Postfix::IsOperator(char ch) const // 检查ch是否为'+','-','*','/','%','^'其中一个
{
	return ch == '+' || ch == '-' || ch == '*' ||
		ch == '%' || ch == '/' || ch == '^';
}

Postfix::Postfix()
{}

Postfix::Postfix(const string& s):
	postfix_exp(s)
{}

void Postfix::set_postfix_exp(const string& s)//设置后缀表达式
{
	postfix_exp = s;
}
double Postfix::Calculate()//计算并将结果返回
{	double left, right, result,exp_value;
    string delimiter=" ";
    int last = 0;
    int next = 0;
    string token;
    try{
        if(postfix_exp.find(delimiter, last) == string::npos){//如果是简单的一个数字，无需计算直接返回
            return(stod(postfix_exp));
        }
        while ((next = postfix_exp.find(delimiter, last)) != string::npos) {//以空格为间隔，分割string
            token = postfix_exp.substr(last, next-last);
            cout << "Get string:"<<token<<endl;
            if(token.empty()){//遇到空白，跳过
                cout<<"└──empty,skipped"<<endl;
                last = next + 1;
                continue;
            }
            if(token.length()==1 && IsOperator(token[0])){//遇到运算符，取出两个数值进行运算然后再压栈
                GetOperands(left, right);
                result=Compute(left, right,token[0] );
                operand_stack.push(result);
                cout<<"└──Push:"<<result<<endl;
            }
            else{//尝试转为double类型数值然后压栈
                double num;
                num=stod(token);
                operand_stack.push(num);
                cout<<"└──Push:"<<num<<endl;
            }
            last = next + 1; 
        }
        token = postfix_exp.substr(last);//还剩余一个子串需要分析
        cout <<"Get string:"<<token<<endl;
        if(token.length()==1 && IsOperator(token[0])){
            GetOperands(left, right);
            result=Compute(left, right,token[0] );
            operand_stack.push(result);
            cout<<"└──Push:"<<result<<endl;
        }
        else if(token.empty()){
            cout<<"└──empty,skipped"<<endl;
        }
        else{//后缀表达式的最后一个字符必须是运算符
            throw "Posifix Calculate: Last position must be an operator";
        }
        exp_value = operand_stack.top();
        cout<<"└──Pop:"<<exp_value<<endl;
        operand_stack.pop();
        if (!operand_stack.empty())//栈内若还有数值则是表达式语法问题
            throw "Posifix Calculate: Too many operands";
    }catch (const std::invalid_argument&) {//不是正确的数字格式
        cerr << "Argument is invalid"<<endl;
        exit(1);
    } catch (const std::out_of_range&) {//超出double范围
        cerr << "Argument is out of range for a double\n";
        exit(1);
    } catch(const char* msg){
        cerr<<msg<<endl;//输出异常信息
        exit(1);
    }

	return exp_value;
}