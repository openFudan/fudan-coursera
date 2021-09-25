#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream read("input.txt");
	ofstream write("output.txt");
	int *p, n, k, i, *q, f = 0, z = 0;
	read >> n;
	p = new int[n];
	for (i = 0, q = p; i<n; i++)
	{
		*q = i + 1;
		q++;
	}
	read >> k;

	while (1)
	{
		q = p;
		while (1) {

			if ((*q) != 0)
			{
				f++; if (f == k) { *q = 0; f = 0; z++; }


				q++; if (z == n - 1) goto ss;

			}
			else q++; if (z == n - 1) goto ss;
			if (*(q)<0) { if (z == n - 1) goto ss;  break; }

		}
	}

ss:q = p;
	for (i = 0, q = p; i<n; i++)
	{
		if ((*(q + i)) != 0) write << *(q + i) << endl;
	}
	read.close();
	getchar();
	return 0;
}