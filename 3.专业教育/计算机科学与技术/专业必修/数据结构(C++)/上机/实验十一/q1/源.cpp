#include"head.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	ifstream file;
	
	file.open("input.txt");
	
	string pre;

	int a, b,i,j,p1,p2,len;

	file >> a >> b;
	Graph g(a);
	int **c;
	(c) = new int *[a];
	for (i = 0; i < a; i++)
		*(c + i) = new int[a];
	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
			c[i][j] = 0;
	while (file)
	{

		file >> p1 >> p2 >> len;
		if (c[p1 - 1][p2 - 1] == 0
			|| len < c[p1 - 1][p2 - 1])
		{
			c[p1 - 1][p2 - 1] = len;

			c[p2 - 1][p1 - 1] = len;
		}

	}
	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
		{
			if (i != j&&c[i][j] == 0)
				c[i][j] = 99999;
		}
	g.ccost(c);
	delete c;
	
	for (i = 0; i < a; i++)
	{
		g.ShortestPath(a, i);
		
	}
	g.makeddistandprint();
	file.close();

	return 0;
}






