#include"head.h"
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream file;
	
	file.open("input.txt");
	

	int a, b, i, j;
	file >> a ;
	Graph g(a);
	int **c;
	(c) = new int *[a];
	for (i = 0; i < a; i++)
		*(c + i) = new int[a];
	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
			c[i][j] = 0;
	

	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
			file >> c[i][j];
		


	g.ccost(c);
	delete c;
	
	g.getmintree();
	
	file.close();

	return 0;
}






