#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	ifstream file;
	ofstream ofile;
	string s;
	file.open("test.txt");
	ofile.open("output.txt");
	
	
	char freedom[7] = { 'f','r','e','e','d','o','m' };
	int i,sum=0,j,k;
	
     while (getline(file, s))
	{
		
	
		for (i = 0; s[i] != '\0'; i++)
		{
			for (j = 0; j < 7&&s[i+j]!='\0'; j++)
			{   
				if (s[i + j] != freedom[j])
					break;
				
			
				if (j == 6&& s[i + j] == freedom[j]) 
				{ sum=sum+1; 
		
				break; }
			}
			
		}
	}
	 ofile << sum << endl;

	return 0;
}






