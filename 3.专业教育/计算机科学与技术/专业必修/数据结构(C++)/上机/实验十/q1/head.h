#ifndef _HEAD_H_
#define _HEAD_H_
#include<iostream>
#include<fstream>
using namespace std;
template <class Type> class LStack;
template <class Type> class Node {
	friend class LStack <Type>;
private:
	Type data; //结点数据
	Node <Type> *link; //结点链指针
public:
	Node(Type d ,Node <Type> *next ) 
	{
		data = d;
		link = next;
	}
};
template <class Type> class LStack {
private:
	Node <Type> *top; //栈顶指针
public:
	LStack() : top(NULL) { }
	void Push(Type x) //进栈
	{
		Node <Type> *p;
		p = new Node <Type>(x, NULL);
		 p->link = top; top = p;
	}
	int Pop(Type *x) //退栈
	{
		Node <Type> *p;
		if (top == NULL) return 0;
		(*x) = top->data; p = top; top = top->link; delete p;
		return 1;
	}
	int GetTop(Type *x)//读取栈顶元素
	{
		if (top == NULL) return 0;
		else {
			(*x) = top->data;
			return 1;
		}
	}
	int IsEmpty() { return (top == NULL) ? 1 : 0; }
};

class BiThrTree;
class BiThrNode {
	friend class BiThrTree;
	friend struct stknode;
	int data;
	class BiThrNode *lchild, *rchild;
public:
	BiThrNode() {}
	BiThrNode(int i) { data = i; lchild = NULL; rchild = NULL; }
	void print(BiThrNode *p)
	{
		if (p != NULL) {
			cout << p->data << endl;
		
			if (p->lchild != NULL)
			{	
				print(p->lchild);
			}
			if (p->rchild != NULL)
			{
				print(p->rchild);
			}
        }
	}
};
struct stknode
{
	BiThrNode * ptr;
	int f;

};
class BiThrTree {
	BiThrNode *root;

public:
	BiThrTree() { root = NULL; }
	BiThrNode * gettree(char* pre, char* mid, int nn);
	void print()
	{
		root->print(root);
	}

	int cutbigger(int xx);
	void midthrough();
	BiThrNode * findparent(int a);
	void postorder();
};
#endif