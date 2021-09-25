#include<iostream>
#include<string>
#include<fstream>
using namespace std;
char ms[10] = "marshtomp";
char pi[8] = "Picachu";
int fit(string& ss, int i,int j)
{
	if ((ms[j]-ss[i])==0|| (ms[j] - ss[i]==32))
	{	
		if (j == 8)
		{
			return 1;
		}
		i++; j++;
		return fit(ss, i, j);
	}
	 return 0;
}
int main()
{
	//0/32
	ifstream is("input.txt");
	ofstream os("output.txt");
	char c;
	int i,rs,j;
	string ss;
	while (is)
	{
		if (!getline(is, ss)) return 0;
		for (i = 0; i < ss.length(); i++)
		{
			rs=fit(ss, i, 0);
			if (rs == 1) 
			{
				break; }
		}

		for (j = 0; j < 7; j++)
			ss[i + j] = pi[j];

		for (; i+j+2<ss.length() ; j++)
		{
			ss[i + j] = ss[i + j + 2];
		}
		ss[i + j] = '\0';
		for (i = 0; ss[i] != '\0'; i++)
			os << ss[i];
		os<< endl;
	}
	is.close();
	return 0;
}




