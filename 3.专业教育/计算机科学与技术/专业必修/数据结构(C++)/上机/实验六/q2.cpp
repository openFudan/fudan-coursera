#include"text.h"
#include<iostream>
using namespace std;
int yanghui(int n, int *a,int b)
{
	int i;
	if (b == n+1) return 0;
	int *p = new int[b + 2];
	
	if (b == 1)
		{
			p[0] = 0;
			p[1] = 1;
			p[2] = 0;
			}
	else
	for (i = 0; i < b + 2; i++)
	{
		p[0] = 0;
		p[b + 1] = 0;
		if (1 <= i&&i <= b )
			p[i] = a[i] + a[i - 1];
	}

	for (i = 0; i < (n - b+1) ; i++)
		cout << " " ;
	for (i = 0; i < b + 2; i++)
		if (p[i]>0) cout << p[i] <<" " ;
	cout << endl;
	b++;
	delete a;
	yanghui(n, p, b);
	return 0;
}
int main()
{
	int n,i;
	cin >> n;
	int *a = new int[n+2];
	yanghui(n, a,1);
	return 0;
}


