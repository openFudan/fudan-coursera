#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	ifstream is("input.txt");
	ofstream os("output.txt");
	int i, k = 1, j, m = 0, n = 0, len = 1, max = 1, N; char temp;
	string ss;
	is >> N;
	string *Q = new string[N];
	for (i = 0; i < N; i++)
	{
		is >> Q[i];
	}
	for (i = 0; i < N; i++)
	{
		m = n = 0; max = 1; len = 1;
		for (j = 1; j < Q[i].length(); j++) {
			k = 1;
			while ((j - k) >= 0 && (j + k) <= (Q[i].length() - 1))
			{
				if (Q[i][j - k] == Q[i][j + k]) {
					if (2 * k + 1>max)
					{
						m = j - k; n = j + k;
						max = 2 * k + 1;
					}
					k++;
				}
				else break;
			}
		}

		for (j = 0; j < Q[i].length(); j++)
		{
			k = 1;
			while ((j - k + 1) >= 0 && (j + k) <= (Q[i].length() - 1))
			{
				if (Q[i][j - k + 1] == Q[i][j + k])
				{
					if (2 * k >= max) { m = j - k; n = j + k; max = 2 * k; }
					k++;
				}
				else break;
			}
		}

		os << n - m + 1;
		os << endl;
	}
	delete[]Q;
	return 0;
}



