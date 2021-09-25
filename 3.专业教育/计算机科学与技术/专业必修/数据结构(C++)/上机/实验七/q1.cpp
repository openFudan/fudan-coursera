#include"q1.h"
#include<iostream>
#include<string>
using namespace std;
void findandset(string pre, string mid, BTNODE<char>& p)//build up a tree by two strings
{

	string a, b;
	char c = pre[0];

	p.data = c;

	char t; int i, j, m = 0, k;
	if (pre.length() == 2)
	{
		for (i = 0; mid[i] != '\0'; i++)
			if (mid[i] == c) break;
		if (i == 0)
		{
			p.fch = NULL;
			p.rch = new BTNODE<char>();
			p.rch->data = mid[1];
		}
		if (i == 1)
		{
			p.rch = NULL;
			p.fch = new BTNODE<char>();
			p.fch->data = mid[0];
		}
	}
	else if (pre.length() == 3)
	{
		p.fch = new BTNODE<char>();
		p.rch = new BTNODE<char>();
		p.fch->data = mid[0];
		p.rch->data = mid[2];
	}
	else {
		p.fch = new BTNODE<char>('a');

		p.rch = new BTNODE<char>('a');
		for (i = 0; mid[i] != '\0'; i++)
			if (mid[i] == c) break;

		for (j = 0; j < i; j++)
			for (k = 0; pre[k] != '\0'; k++)
				if ((mid[j] == pre[k]) && k>m)  m = k;

		a = pre.substr(1, m);
		b = mid.substr(0, i);
		findandset(a, b, *(p.fch));

		a = pre.substr(m + 1, pre.length() - m - 1);
		b = mid.substr(i + 1, mid.length() - i - 1);
		findandset(a, b, *(p.rch));
	}
}
void output(BTNODE<char>& r)//output the tree by backorder 
{
	BTNODE<char>* p;
	p = r.fch;
	if (p != NULL)
		output(*p);
	p = r.rch;
	if (p != NULL)
		output(*p);
	cout << r.data;
}
int main()
{
	BTNODE<char> r;
	string pre, mid;

	getline(cin, pre);
	getline(cin, mid);
	findandset(pre, mid, r);
	output(r);



	return 0;
}



