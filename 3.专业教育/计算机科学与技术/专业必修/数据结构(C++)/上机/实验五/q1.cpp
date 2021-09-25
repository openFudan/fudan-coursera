#include"text.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string s;
	getline(cin, s);
	LSTK<int> n;
	int i = 0, sum = 0;
	for (i = 0; s[i] != '\0'; i++)
	{

		if (0 <= (s[i] - '0') && (s[i] - '0') <= 9) {
			sum = 10 * sum + s[i] - '0';
		}
		if (s[i] == '"'&&sum>0) { n.push(sum); sum = 0; }
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
		{
			char c = 'a';
			c = s[i];
			int a = 0, b = 0;
			switch (c)
			{
			case '+':
				a = n.pop();
				b = n.pop();
				n.push(a + b);
				break;
			case '-':
				a = n.pop();
				b = n.pop();
				n.push(b - a);
				break;
			case '*':
				a = n.pop();
				b = n.pop();
				n.push(a * b);
				break;
			case '/':
				a = n.pop();
				b = n.pop();
				n.push(b / a);
				break;
			}
		}
	}
	cout << n.gettop() << endl;
	return 0;
}


