#include<iostream>
#include<string>
using namespace std;
int search(int *a, int aim)
{
	int s = 0;
	int ai = aim, i = 0;
	for (i = 0; a[i] > 0; i++)
	{
		aim = ai;
		if (a[i]>0 && a[i] <= aim)
		{
			aim -= a[i];
			cout << a[i] << " ";
			if (aim == 0) {
				s++;
				cout << endl;

			}
			else {
				s += search(a + i, aim);
			}
		}
	}
	return s;
}
int main()
{
	while (cin)
	{
		int i, sum = -1, j = 0, aim, temp;
		string c;
		int a[10];
		getline(cin, c);
		for (i = 0; c[i] != '\0'; )
		{
			while (1) {
				if (c[i] != '\0')
				{
					if ('0' <= c[i] && c[i] <= '9')
					{
						if (sum == -1) sum = c[i] - '0';
						else sum = sum * 10 + (c[i] - '0');
						++i;
					}
					else { ++i; break; }
				}
				else break;
			}
			if (sum >= 0) { a[j] = sum; sum = -1; j++; }
		}

		for (i = 0; a[i] > 0; i++)
		{

		}
		aim = a[i - 1];
		a[i - 1] = -1;//a[],aim
		for (i = 0; a[i] > 0; i++)
			for (j = i + 1; a[j] > 0; j++)
			{
				if (a[i] < a[j]) {
					temp = a[j];
					a[j] = a[i];
					a[i] = temp;
				}
			}
		if (aim == 0) cout << 1 << endl;
		else {
			cout << search(a, aim) << endl;
		}
		c.clear();
	}
	return 0;
}
