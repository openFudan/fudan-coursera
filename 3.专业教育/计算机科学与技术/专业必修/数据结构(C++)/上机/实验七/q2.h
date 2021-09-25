#ifndef _Q2_H_
#define _Q2_H_
#include<iostream>
template <class Type> class BTNODE {
public: 	
	Type a;
	BTNODE <Type> * fch;
	BTNODE <Type> * nbr;
     BTNODE() : fch(NULL), nbr(NULL) { }	
	 BTNODE(Type x) { a = x; }
};

#endif
