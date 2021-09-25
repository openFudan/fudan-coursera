#include"text.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	LSTK<int> a, b;
	int i=0,j,k, temp,sum=0,m=0;
	string s;
	getline(cin, s);
	for (i = 0; s[i]!='\0'; i++)
	{
		if (0 <= (s[i] - '0') && (s[i] - '0') <= 9) {
				sum = 10 * sum + s[i] - '0';
				
			}
			if (((s[i+1]=='\0')||(s[i+1] == ' '))&&sum > 0) { a.push(sum); sum = 0; m++; }
	}
	for (k= m-1; k >=1; k--)
	{
		for (j = 1; j <= k; j++)
		{
			temp = a.pop();
			b.push(temp);

			if (a.gettop() < b.gettop())
			{
				temp = a.gettop();
				a.pop();
				a.push(b.gettop());
				b.pop();
				b.push(temp);
			}
		}
		while (!b.isemp())
		{
			temp = b.pop();
			a.push(temp);
		}
	}
	while (!a.isemp())
		cout << a.pop() << endl;
	return 0;
}



