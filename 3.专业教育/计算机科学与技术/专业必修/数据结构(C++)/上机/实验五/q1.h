#ifndef _TEXT_H_
#define _TEXT_H_
#include<iostream>
template<class T> struct ListNode
{
	T data;
	ListNode<T> * link;
};
typedef  ListNode<int> nod;
template<class T> class LSTK
{
private:
	nod *top;
public:
	LSTK() { top = NULL; }
	void push(T x)
	{
		nod * p = (nod *)malloc(sizeof(nod));
		p->data = x;
		p->link = top;
		top = p;
	}
	T pop() {
		if (top == NULL) return -1;
		T y = top->data;
		nod * p = top;
		top = top->link;
		delete p;
		return y;
	}
	T gettop()
	{
		return top->data;
	}
	int isemp()
	{
		if (top == NULL) return 1;
		else return 0;
	}
};
#endif
