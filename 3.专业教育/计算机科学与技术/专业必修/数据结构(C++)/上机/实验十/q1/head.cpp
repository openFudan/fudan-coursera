#include"head.h"
#include<iostream>
#include<fstream>
BiThrNode * BiThrTree::gettree(char* pre, char* mid, int nn)
{
	BiThrNode* p = NULL;
	char* pren, midn;
	int i, j, n = 0;
	int a, b = 0, sum = 0, temp;
	for (i = 0; i<=nn; i++)
	{
		if (0 <= (pre[i] - '0') && (pre[i] - '0') <= 9 && pre[i + 1] != '\0')
		{
			sum = sum * 10 + pre[i] - '0';
		}
		else {
			if (pre[i + 1] == '\0')
				sum = sum * 10 + pre[i] - '0';
			break;
		}
	}
	if (root == NULL) { root = new BiThrNode(sum); p = root; }
	else  p = new BiThrNode(sum);
	for (j = 0; j <= nn; j++)
		if (0 <= (mid[j] - '0') && (mid[j] - '0') <= 9 && mid[j + 1] != '\0')
		{
			b = b * 10 + mid[j] - '0';
		}
		else {
			if (mid[j + 1] == '\0')
				b = b * 10 + mid[j] - '0';

			if (b == sum)
			{
				temp = sum;

				while (1)
				{
					if (temp = (temp / 10)) n++;
					else
					{
						n++; 
						break;
					}
				}

				if (j - n - 1 >= 1)
				{

					p->lchild = gettree(pre + i + 1, mid, j - n - 1);

				}
				else {

					p->lchild = NULL;
				}
				if (nn - j - 1 >= 1)
				{
					p->rchild = gettree(pre + i + j - n + 1, mid + j + 1, nn - j - 1);///ÊÕÎ²£¬º¢×ÓÎª¿Õ

				}
				else {

					p->rchild = NULL;
				}
				break;
			}
			b = 0;
			n = 0;
		}
		return p;
}

int BiThrTree::cutbigger(int xx)
{
	BiThrNode *par,  *pp = root;
	BiThrNode **p = &pp;
	LStack<BiThrNode *> stack;

	
	if (root != NULL)
	{
		while ((pp)!=NULL||!stack.IsEmpty())
		{
			
			while ((pp) != NULL)
			{
				stack.Push((pp));
				pp = (pp)->lchild;		
				
			}
			if(!stack.IsEmpty())
			{
				 stack.Pop(p);
				 pp = *p;
				 if ((pp)->data >= xx)
				 {
					 par = findparent((pp)->data);
					 if (par->lchild!=NULL&&(pp)->data == par->lchild->data)
					 {
						 par->lchild = (pp)->lchild;
						 (pp) = NULL;
					 }
					 else
					 { 
						 par->rchild = (pp)->lchild; 
						 (pp) = (pp)->lchild;
					 }
				 }
				 else pp = (pp)->rchild;
			}
		}

	}
	
	return 1;
}
void BiThrTree::midthrough()
{
	
	if (root != NULL)
	{
		BiThrNode  *p = root;
	 BiThrNode  **pp = &p;
	 LStack<BiThrNode *> stack;
	
	 ofstream ofile;
	 
	 ofile.open("output.txt", ios::out|ios::app);
		while ((p) != NULL || !stack.IsEmpty())
		{
			while ((p) != NULL)
			{
				stack.Push((p));
				p = (p)->lchild;
			}
			if (!stack.IsEmpty())
			{
				stack.Pop(pp);
				p = *pp;
				ofile << (p)->data << " ";
				
				p = (p)->rchild;
			}
		}
		ofile << endl;
		
	  ofile.close();
	}
	
}
BiThrNode* BiThrTree::findparent(int a)
{
	LStack<BiThrNode *> stack;
	BiThrNode* p = root;
	if (root != NULL)
	{
		while (p != NULL)
		{
			if (p->lchild != NULL)
			{
				if (p->lchild->data == a)
					break;
			}
			if (p->rchild != NULL)
			{
				if (p->rchild->data == a)
					break;
			}
			if (p->data > a) p = p->lchild;
			if (p->data < a) p = p->rchild;
		}
	}
	return p;
}
void BiThrTree::postorder()
{
	LStack<stknode> s;
	stknode w;
	ofstream ofile;
	ofile.open("output.txt", ios::out | ios::app);
	BiThrNode *p = root;
	do {
		while (p != NULL)
		{
			w.ptr = p;
			w.f = 0;
			s.Push(w);
			p = p->lchild;
		}
		if (!s.IsEmpty())
		{
			s.Pop(&w);
			p = w.ptr;
			switch (w.f)
			{
			case 0:w.f = 1;
				s.Push(w);
				p = p->rchild;
				break;
			case 1: {ofile << p->data << " "; p = NULL; break; }
			}
		}
	} while (p != NULL || !s.IsEmpty());
	ofile << endl;
	ofile.close();
}
