#include<iostream>
#include<fstream>
using namespace std;
	int a[3000][3000];
	int min(int a, int b, int c)
	{
		if (a < b) { return (a<c) ? a : c; }
		else { return (b<c) ? b : c; }
	}
	int main()
	{
		ifstream read("input.txt");
		ofstream write("output.txt");
		int m=1, n; int t, number; int i, j; bool in; 
		
			read  >> n; 
			for (i = 0; i <n; ++i)
			{
				for (j = 0; j < n; ++j)
				{
					read>> in; if (in) { a[i][j] = 0; }
					else { a[i][j] = 1; }
				}
			}
			for (i = 1; i < n; ++i)
			{
				for (j = 1; j < n; ++j)
				{
					if (a[i][j] != 0)

					{
						a[i][j] += min(a[i - 1][j], a[i - 1][j - 1], a[i][j - 1]);
					}
				}
			}

			int biggest = a[0][0];
			for (i = 0; i < n; ++i)
			{
				for (j = 0; j < n; ++j)

				{
					
					if (a[i][j] == biggest) { m++; }
					if (a[i][j] > biggest) { biggest = a[i][j];m=1; }
				}

			}
			write << biggest*biggest << " "<<m<<endl;
			read.close();
		 return 0;
	}
	