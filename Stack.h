#ifndef MYSTACK
#define MYSTACK

#include <iostream>
using namespace std;

template<class T> struct Node {//自定义链表节点结构体
    T value;
    Node<T>* next;
    Node() :next(nullptr) {};
    Node(T t) : value(t), next(nullptr) {}
};

template <typename T> class Stack {//自定义栈类
    int length; //栈元素的数量
    Node<T> *head; //指向头节点的头指针
public:
    Stack() { length = 0; head = new Node<T>; }//构造函数
    void push(const T value); //入栈
    T pop();  //出栈
    const T top(); //获取栈顶元素

    void print(); //打印栈
    int size(); //获取栈内元素个数
    bool empty(); //判空
};

template<typename T>
void Stack<T>::push(const T value) {
    Node<T>* pnode = new Node<T>(value);
    pnode->next = head->next;
    head->next = pnode;
    length++;
}


template<typename T>
T Stack<T>::pop() {
    Node<T>* pnode = head->next;
    if (pnode==nullptr)
        throw runtime_error("Stack is empty");
    T pdata = pnode->value;
    head->next = head->next->next;
    length--;
    delete pnode;
    return pdata;
}

template<typename T>
const T Stack<T>::top() {
    if (head->next==nullptr)
        throw runtime_error("Stack is empty");
    return head->next->value;
}

template<typename T>
void Stack<T>::print() {
    Node<T> *pnode = head->next;

    while (pnode != nullptr)
    {
        cout << pnode->value << endl;
        pnode = pnode->next;
    }
}
template<typename T>
int Stack<T>::size() {
    return length;
}

template<typename T>
bool Stack<T>::empty() {
    return length == 0;
}

#endif