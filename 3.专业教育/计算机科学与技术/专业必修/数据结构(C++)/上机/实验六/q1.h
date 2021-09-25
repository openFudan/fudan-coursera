#ifndef _TEXT_H_
#define _TEXT_H_
#include<iostream>
template <class Type> class LStack;
template <class Type> class Node {
	friend class LStack<Type>;
	Type data;
	Node <Type> *link;
};
template <class Type> class LStack {
private:
	Node <Type> *top;
public:
	LStack() { top = NULL; }
	void push(Type x) {
		Node <Type> *p;
		p = new Node <Type>;
		p->data = x; p->link = top; top = p;
	}
	int empty()
	{
		if (top == NULL)
			return 1;
		else return 0;
	}
	Type gettop()
	{
		if (top == NULL) { cout << "No elements" << endl; return 0; }
			return top->data;
	}

	int pop(Type *x) {
		
		Node <Type> *p;
		if (top == NULL) return -1;
		*x = top->data; p = top; top = top->link; delete p;
		return 0;
	}
	~LStack() {
		while (top != NULL) {
			Node <Type> *p = top;
			top = top->link;
			delete p;
		}
	}
};
#endif
