#include"q1.h"
#include<iostream>
#include<string>

using namespace std;

int main()
{


	int a[100],j=0, c=0,i,m,n;
	BiThrTree t;
	


	string s;
	getline(cin, s);
	cin >> m >> n;
	for (i = 0; i < s.length(); i++)//get the number from string given
	{
		if((i==s.length()-1)&& 0 <= (s[i] - '0') && (s[i] - '0') <= 9){//the last char in the string
			if (0 <= (s[i - 1] - '0') && (s[i - 1] - '0') <= 9)
			{
				c = c * 10 + (s[i] - '0');
				a[j] = c;
				j++;
			}
			else {
				a[j] = (s[i] - '0');
				
				j++;
			}
		}
		else {//not the last char in the tree
			if (0 <= (s[i] - '0') && (s[i] - '0') <= 9)
			{
				if (c == -2) c = 0;
				if (0 <= (s[i+1] - '0') && (s[i+1] - '0') <= 9) {
					c = c * 10 + (s[i] - '0');				
				}
				else {
					c = c * 10 + (s[i] - '0');
					a[j] = c;
					j++;
				}
			}
			else if (s[i] == 'n') { c = -1; a[j] = c; j++; }
			else c = -2;
		}
	}

	t.construct(a,j);//build up a tree according to the given information
	cout << t.comances(m, n) <<  endl;//find the common ancestor of two numbers
	return 0;
}






