#ifndef _TEXT_H_
#define _TEXT_H_
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
ofstream out("output.txt");
template <class t> class list;
template <class t> class listnode
{
	friend class list<t>;
public:
	listnode() { a = 0; next = NULL; }
	listnode(int n) { a = n; next = NULL; }
	int getdata() { return a; }

private:
	int a;
	listnode<t> * next;
};
template <class t> class list
{
public:
	list() { head = tail = NULL; }
	list(int n)
	{
		head = new listnode<t>();
		head->a = n;
		head->next = NULL;
	}
	int add(int i)
	{
		listnode<t>* p = head, *q;
		q = new listnode<t>();
		q->a = i;
		q->next = NULL;
		if (head == NULL)
		{
			head = q;
		}
		else
		{

			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = q;
			p = NULL;
			delete p;
		}
		return 1;
	}
	int  remove(int i)
	{
		int f;
		if (head == NULL) return 0;
		listnode<t>* p = head, *q =p->next;
		for (;q!=NULL; )
		{
		
			if (q->a == i)
			{
				p->next = q->next;
				q = q->next;
				f = 1;
			}
			else {
				p = p->next;
				q = q->next;
			}

		}
		if (f == 1) return 1;
		else return 0;
	}
	int find(int i)
	{
		listnode<t>* p = head;
		if (head == NULL)  return 0;
		else {
			while (p != NULL)
			{
				if (p->a == i) return 1;
				p = p->next;
			}
			return 0;
		}
	}

	listnode<t>* printList()
	{
		if (head == NULL) cout << "None" << endl;
		else
		{
			listnode<t>* q = head;
			while (q != NULL)
			{
				cout << q->a << " ";
				q = q->next;
			}
			cout <<endl;
		}
		
		return head;
	}

private:
	listnode<t> *head, *tail;
};
#endif
