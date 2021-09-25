#include"q2.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	ifstream file;
	ofstream ofile;
	string pre,mid;
	file.open("input.txt");
	ofile.open("output.txt");
	getline(file, pre);
	getline(file, mid);
	char *p=&pre[0], *m=&mid[0];
	int i;
	BiThrTree tree;
	
	tree.gettree(p,m,pre.length());

		i = tree.midthrough();
		if (i == 0) ofile << "False" << endl;
		else ofile<< "Ture" << endl;
		file.close();
		ofile.close();
	return 0;
}






