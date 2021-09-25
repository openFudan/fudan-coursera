#ifndef _HEAD_H_
#define _HEAD_H_
#include<iostream>
#include<fstream>
using namespace std;

const int MAXINT = 9999;


class Graph { 
private:
	int VerticesMaxNumber;
	float **Cost;
	
	float *Dist;
	float **ddist;	//store the shortest path for all vertices
	int *Pre;
	int *S;
public:
	Graph(int MaxNumber)
	{
		int i,j;
		VerticesMaxNumber = MaxNumber;
		Cost = new float *[VerticesMaxNumber];
		ddist = new float *[VerticesMaxNumber];
		for (i = 0; i < VerticesMaxNumber; i++)
		{
			*(Cost + i) = new float[VerticesMaxNumber];
			*(ddist + i) = new float[VerticesMaxNumber];
		}
		for (i = 0; i < VerticesMaxNumber; i++)
			for (j = 0; j < VerticesMaxNumber;j++)
		{
			Cost[i][j] = 0;
			ddist[i][j] = 0;
		}
		Dist = new float [VerticesMaxNumber];
		Pre = new int [VerticesMaxNumber];
		S = new int [VerticesMaxNumber];
		for (i = 0; i < VerticesMaxNumber; i++)
		{
			Dist[i] = 0;
			Pre[i] = 0;
			S[i] = 0;
		}
	}
	void ccost(int **c)
	{
		int i, j;
		for (i = 0; i < VerticesMaxNumber; i++)
			for (j = 0; j < VerticesMaxNumber; j++)
			{
				Cost[i][j] = c[i][j];
			}
	}
	void print()
	{
		int i,j;
		for (i = 0; i < VerticesMaxNumber; i++)
		{
			for (j = 0; j < VerticesMaxNumber; j++)
				cout << Cost[i][j] << " ";
			cout << endl;
		}
	}
	void ShortestPath(int n, int v);//seek for the shortest path for vertice v
	void makeddistandprint();//print ddist

};
#endif