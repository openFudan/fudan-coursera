#include"q2.h"
#include<iostream>

BiThrNode * BiThrTree::gettree(char* pre, char* mid, int nn)
{
	BiThrNode* p = NULL;
	char* pren, midn;
	int i, j, n = 0;
	int a, b = 0, sum = 0, temp;
	for (i = 0; i<nn; i++)
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

int BiThrTree::midthrough()
{
	BiThrNode **p = &root;
	LStack<BiThrNode *> stack;

	if (root != NULL)
	{
		stack.Push(root);
		stack.GetTop(p);

		while (stack.Pop(p))
		{
			if ((*p)->rchild != NULL)
			{

				if ((*p)->rchild->lchild != NULL)
					if ((*p)->rchild->lchild->data < (*p)->data)
						return 0;
				if ((*p)->rchild->data < (*p)->data)
					return 0;
				else stack.Push((*p)->rchild);
			}
			if ((*p)->lchild != NULL)
			{

				if ((*p)->lchild->rchild != NULL)
					if ((*p)->lchild->rchild->data >(*p)->data)
						return 0;
				if ((*p)->lchild->data > (*p)->data)
					return 0;
				else stack.Push((*p)->lchild);
			}
		}
	}
	return 1;
}