#include"head.h"
#include<iostream>
#include<fstream>
void Graph::ShortestPath(int n,int v)
{
	int i, j, k;
	float Min;
	for (i = 0; i < n; i++)
	{
		Dist[i] = Cost[v][i];
		S[i] = 0;
		if (Dist[i]<MAXINT)
			Pre[i] = v;
		else Pre[i] = 0;
	}
	S[v] = 1;
	Pre[v] = 0;

	for (i = 0; i < n; i++)
	{
		Min = MAXINT;
		k = 0;
		for (j = 0; j < n; j++)

			if (S[j] == 0)
				if (Dist[j] != 0 && Dist[j]<Min)
				{
					Min = Dist[j];
					k = j;
				}
		if (k == 0) continue;
		S[k] = 1;


		for (j = 0; j < n; j++)
			if (S[j] == 0 && Cost[k][j]<MAXINT)
				if (Dist[k] + Cost[k][j]<Dist[j])
				{
					Dist[j] = Dist[k] + Cost[k][j];
					Pre[j] = k;
				}
	}
	for (i = 0; i < n; i++)
		ddist[v][i] = Dist[i];
}
void Graph::makeddistandprint()
{
	ofstream ofile;
	ofile.open("output.txt");
	int i, j;
	for (i = 0; i < VerticesMaxNumber; i++)
	{
		for (j = 0; j < VerticesMaxNumber; j++)
		{
			ddist[i][j] = ddist[i][j]>ddist[j][i] ? ddist[j][i] : ddist[i][j];
			ofile << ddist[i][j] << " ";
		}
		ofile << endl;
	}
	ofile.close();
}

