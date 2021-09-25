#include"head.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	ifstream file;
	ofstream ofile;
	file.open("input.txt");
	
	string pre,mid;
	int xx;
	
	file >> xx;
	while (1)
	{
		getline(file, pre);
		if (0 <= pre[0] - '0'&&pre[0] - '0' <= 9)
			break;
	}
	while (1)
	{
		getline(file, mid);
		if (0 <= mid[0] - '0'&&mid[0] - '0' <= 9)
			break;
	}
	char *p=&pre[0], *m=&mid[0];
	int i;
	BiThrTree tree;
	
	tree.gettree(p,m,pre.length());//build up a tree
	tree.cutbigger(xx);//cut up the node whose data >=xx
	tree.midthrough();//mid order 
	tree.postorder();// post order
	file.close();

	return 0;
}






