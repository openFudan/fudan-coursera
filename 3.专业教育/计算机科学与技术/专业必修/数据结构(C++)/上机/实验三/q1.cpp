#include"text.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	string str;
	char l;
	int i = 0, sum = 0, f = 0, k;
	list<int> a;
	cout << "please input commands" << endl;
	while (cin)
	{
		getline(cin, str);
		l = str[0];
		sum = 0;
		f = 0;
		for (i = 0; str[i] != '\0'; ++i)
		{

			if (str[i] == '-')
				f = 1;
		}

		for (i = 0; str[i] != '\0'; ++i)
		{

			if (str[i] >= '0'&&str[i] <= '9')
				sum = sum * 10 + (str[i] - '0');

		}
		switch (l)
		{
		case'a':
		{
			if (f == 1) k = a.add(-sum);
			else k = a.add(sum);
			if (k == 1) { cout << "ture" << endl; break; }
			else { cout << "false" << endl; break; }
		}
		case'r':
		{
			if (f == 1) k = a.remove(-sum);
			else k = a.remove(sum);
			if (k == 1) { cout << "ture" << endl; break; }
			else { cout << "false" << endl; break; }
		}
		case'f':
		{
			if (f == 1) k = a.find(-sum);
			else k = a.find(sum);
			if (k == 1) { cout << "ture" << endl; break; }
			else { cout << "false" << endl; break; }
		}
		case'p': {a.printList(); break; }
		}
	}
	
	return 0;
}
