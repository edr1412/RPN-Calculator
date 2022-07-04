#include "Postfix.h"
#include "Infix.h"
using namespace std;

int main(){
	string p;
	cout<<"Hi,please input an Infix Expression"<<endl;
	cout<<"Example:"<<endl;
	cout<<"\t1+ 2 *(3 -4/5.123 )- 6 / 7 ^2.321"<<endl;
	cout<<"\t4 + (9 %4) /(9.5 -6^ 1.3)-3987"<<endl;
    cout<<"\t  --1+ 9.8 *( - ( 3 -4.5 /6.7)^8 )"<<endl;
	do{
		cout<<">";
		getline(cin,p);//接受输入
	}while(p.empty());
	
	cout << "[*]Infix Expression:{" << p <<"}"<<endl;
	string q=Infix(p).ToPostfix();//中缀转后缀
    cout << "[+]Postfix Expression:{" << q <<"}"<< endl;
    double r=Postfix(q).Calculate();//计算后缀表达式结果
    cout<<"[+]Result: "<<r<<endl;
	return 0;
}