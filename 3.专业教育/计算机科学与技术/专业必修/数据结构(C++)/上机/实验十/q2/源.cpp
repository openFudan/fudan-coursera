//#include"head.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	ifstream file;
	ofstream ofile;
	file.open("input.txt");
	ofile.open("output.txt");
	string pre;
	int i,sum=0,g=0,n=0,j=0,min=0,mini=0;
	char c = 'A';
		
	while (getline(file, pre))
	{
		n = 0; 
		
		int *p;
		p = new int[pre.length()];
		for (i = 0; i <= pre.length(); i++)
		{
			
				if (0 <= (pre[i] - '0') && (pre[i] - '0') <= 9)
				{
					sum = sum * 10 + pre[i] - '0';
				}
				else {
					if (0 <= (pre[i - 1] - '0') && (pre[i - 1] - '0') <= 9)
					{
						p[n++] = sum;
						sum = 0;
					}
				}
			
		}
		c = 'A';
		c += g;
		ofile << c << ":";
		for (i = 0; i < n;i++ )
		{
			min = 9999;
			mini = 0;
			for (j = 0; j < n; j++)
			{
				if (p[j] <min&&p[j]!=0) 
				{ 
					min = p[j];
					mini = j;
				}				
			}
			if (min <9999) {
				p[mini] = 99999;
				c = 'A';
				c +=mini;
				ofile << c << " ";
			}
		}
			
		g++;
		delete p;
		ofile << endl;
	}
	
	
	file.close();
	ofile.close();
	return 0;
}






