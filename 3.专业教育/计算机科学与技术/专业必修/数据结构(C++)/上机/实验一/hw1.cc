#include <iostream>
using namespace std;
//n  a1 a2 ... an
//T
//b1 b2.. bi

void main()
{
    int n,T,i,k;
	cin>>n;
    int *p= new int[n];
	for(i=0;i<n;i++)
	{
		cin>>p[i];
	}
    cin>>T;
    int *q= new int[T];
    for(i=0;i<T;i++)
	{
		cin>>q[i];
	}

	int *p1= new int[n];
	for(i=0;i<n;i++)
	{
		p1[i]=n;
	}

   for(i=0;i<n;i++)
		for(k=0;k<n;k++)
		{
			if(p[i]>p[k]) 
				p1[i]--;
		}
    for(i=0;i<T;i++)
	{
		for(k=0;k<n;k++)
			if(p1[k]==q[i]) 
        cout<<p[k]<<endl;
	}

	cout<<"Hello World"<<endl;
}