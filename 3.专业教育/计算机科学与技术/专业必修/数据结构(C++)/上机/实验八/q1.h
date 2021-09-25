#ifndef _Q1_H_
#define _Q1_H_
#include<iostream>
using namespace std;
template <class Type> struct node
{
	Type data; struct node *link;
};
template <class Type> class
LinkedQueue {
	typedef node <Type> NODE;
private:
	NODE *head, *tail;
public:
	LinkedQueue() {
		head = tail = NULL;
	}
	void enqueue(Type x) {
		NODE *p;
		p = new NODE();
		p->data = x;
		p->link = NULL;
		if (head == NULL) head = p;
		else tail->link = p;
		tail = p;
	}
	int dequeue(Type *py) {
		NODE *p;
		if (head == NULL) return 1;
		*py = head->data;
		p = head;
		head = head->link;
		delete p;
		return 0;
	}
	int isempty()
	{
		if (head == NULL) return 1;
		else return 0;
	}
};
class BiThrTree;
class BiThrNode {
	friend class BiThrTree;
	int data;
	class BiThrNode *lchild, *rchild;
	BiThrNode(int i) { data = i; lchild = NULL; rchild = NULL; }
	void print(BiThrNode *p)
	{
		if (p != NULL) {
			cout << p->data << endl;
		}
		if (p->lchild != NULL) print(p->lchild);
		if (p->rchild != NULL) print(p->rchild);

	}
};
class BiThrTree {
	BiThrNode *root;
public:
	BiThrTree() { root = NULL; }
	void print()
	{
		root->print(root);
	}
	BiThrNode * findi(int i, BiThrNode *p);//find the node which has data i from the tree

	int comances(int a, int b);//find the common ancestor of two numbers

	BiThrNode * parent(BiThrNode * par, BiThrNode * p);//find the parent of *p from the root named *par

	void construct(int *p, int n);//build up a tree according to the given information
	
};
#endif