#ifndef _Q1_H_
#define _Q1_H_
#include<iostream>
template <class Type> class BTNODE {
public:
	Type data;
	BTNODE <Type> * fch;
	BTNODE <Type> * rch;
	BTNODE() : fch(NULL), rch(NULL) { }
	BTNODE(Type item,
		BTNODE <Type> *left = NULL,
		BTNODE <Type> *right = NULL) :
		data(item), fch(left), rch(right) { }
	void setdata(Type d) { data = d; }
	BTNODE<Type> * setleft(BTNODE <Type> *p)
	{
		fch = p;
		return p;
	}
	BTNODE<Type> * setr(BTNODE <Type> *p)
	{
		rch = p;
		return p;
	}
	Type GetData() const { return data; }

};

#endif