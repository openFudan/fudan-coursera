#include"head.h"
#include<iostream>
#include<fstream>

void Graph::getmintree()
{
	ofstream ofile;
	ofile.open("output.txt");

	{
		int i, j, k, e = 0, d = 0, n = 0;
		int min = MAXINT, jmin, kmin; int sum = 0;
		for (i = 0; i < VerticesMaxNumber - 1; i++)
		{
			min = MAXINT;

			for (j = 0; j < VerticesMaxNumber; j++)
				for (k = 0; k < VerticesMaxNumber; k++)
				{
					if (j != k&&Cost[j][k] != -1 && Cost[j][k] < min)
					{
						min = Cost[j][k];
						jmin = j;
						kmin = k;
					}

				}
			sum += min;
			Cost[jmin][kmin] = -1;
			Cost[kmin][jmin] = -1;
			Dist[jmin]++;
			Dist[kmin] ++;
			e++;
			for (d = 0, n = 0; d < VerticesMaxNumber; d++)
				if (Dist[d] != 0) n++;
			if (n == e)
			{
				i--;
				sum -= min;
				Dist[jmin]--;
				Dist[kmin]--;
				e--;
			}

		}
		ofile << sum << endl;
	}
	ofile.close();
}


