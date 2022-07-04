class ComparableOp//带优先度的符号
{
	public:
		ComparableOp();
		ComparableOp(char ch);
		friend bool operator>= (const ComparableOp& left,const ComparableOp& right);//友元函数，重载运算符>=
		char getOp() const;//返回op值
	private:
		char op;
		int inputPrecedence;//新来时的优先级
		int stackPrecedence;//栈内时的优先级
};