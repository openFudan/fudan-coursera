#include"q2.h"
#include<iostream>
void BiThrTree::construct(int *p, int n)
{
	int i = 0, a = 0;
	LinkedQueue<int> q;
	q.enqueue(p[i]);
	BiThrNode *b;
	while (1)
	{
		if (q.dequeue(&a) == 1) break;

		if (a != -1) {
			if (root == NULL)

				root = new BiThrNode(a);
			b = findi(a, root);
			if (i < n - 1) {

				i++;
				q.enqueue(p[i]);
				b->lchild = new BiThrNode(p[i]);
			}
			else break;

			if (i < n - 1) {
				i++;
				q.enqueue(p[i]);
				b->rchild = new BiThrNode(p[i]);
			}
			else break;

		}
	}
}
BiThrNode * BiThrTree::findi(int i, BiThrNode *p)
{
	if (p != NULL) {
		if ((p->data == i) && (p->lchild == NULL || p->rchild == NULL)) return p;
		else {
			BiThrNode *q = findi(i, p->lchild);
			if (q != NULL)
				return q;
			else {
				q = findi(i, p->rchild);
				if (q != NULL)
					return q;
				else return NULL;
			}
		}
	}
	else return NULL;
}
void BiThrTree::zigzagoutput()
{
	LinkedQueue<BiThrNode *> q1, q2;
	int a[100], f = 0, j = 0, i;
	BiThrNode *x;

	if (root != NULL)
	{
		q1.enqueue(root);
		cout << root->data << endl;
		while (1)
		{
			if (q1.isempty() == 1 && q2.isempty() == 1)
				break;
			while (f == 0)
			{
				if (q1.isempty() != 1) {
					q1.dequeue(&x);
					if (x->lchild != NULL&&x->lchild->data >= 0)
					{
						q2.enqueue(x->lchild);
						a[j] = x->lchild->data;
						j++;
					}
					if (x->rchild != NULL&&x->rchild->data >= 0)
					{
						q2.enqueue(x->rchild);
						a[j] = x->rchild->data;
						j++;
					}


				}
				else {
					f = 1;
					for (i = j - 1; i >= 0; i--)
						cout << a[i] << " ";//output the levet from right to left
					j = 0;
					if (q2.isempty() != 1) cout << endl;
					break;
				}
			}
			if (q1.isempty() == 1 && q2.isempty() == 1)
			{

				break;
			}
			while (f == 1)//output the levet from left to right
			{
				if (q2.isempty() != 1) {
					q2.dequeue(&x);
					if (x->lchild != NULL&&x->lchild->data>0)
					{
						q1.enqueue(x->lchild);
						cout << x->lchild->data << " ";
					}
					if (x->rchild != NULL&&x->rchild->data>0)
					{
						q1.enqueue(x->rchild);
						cout << x->rchild->data << " ";
					}
				}
				else {
					f = 0;
					if (q1.isempty() != 1)	cout << endl;
					break;
				}
			}
			if (q1.isempty() == 1 && q2.isempty() == 1)
				break;
			
		}
	}
}





