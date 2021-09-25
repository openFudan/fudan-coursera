#include <iostream>
#include <istream>
#include <ostream>
using namespace std;
//n a1 a2 ... an
//k b1 b2 ... bk
//k y n
void main()
{
   int k,i,m,n;
   cin>>n;
	int *p=new int[n];
    for(i=0;i<n;i++)
	{
	   cin>>p[i];
	}
   cin>>k;
	int *q=new int[k];
    for(i=0;i<k;i++)
	{
	   cin>>q[i];
	}
	
	int *q1=new int[k];
    for(i=0;i<k;i++)
	{
	   q1[i]=0;
	}



for(m=0;m<k;m++)
     for(i=0;i<n;i++)
	{
	   if(q[m]==p[i])  q1[m]=1;
	}
	 for(m=0;m<k;m++)
		 if(q1[m]==1) cout<<"y"<<endl;
		 else cout<<"n"<<endl;
    
	
	
}