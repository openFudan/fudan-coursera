#include"q1.h"
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
int BiThrTree::comances(int a, int b)
{
	if (root->data == a) return a;
	if (root->data == b) return b;
	BiThrNode *p = findi(a, root);
	BiThrNode *q = findi(b, root);

	while (1)
	{

		if (findi(b, p) != NULL) {
			return p->data;

		}
		else p = parent(root, p);
		if (findi(a, q) != NULL) {
			return q->data;

		}
		else q = parent(root, q);
	}
}
BiThrNode * BiThrTree::parent(BiThrNode * par, BiThrNode * p)
{
	if (par->lchild == p || par->rchild == p) return par;
	else {

		BiThrNode * q;
		if ((par->lchild != NULL) && (q = parent(par->lchild, p)) != NULL)
			return q;
		else if ((par->rchild != NULL) && (q = parent(par->rchild, p)) != NULL)  return q;
		else return NULL;
	}
}

