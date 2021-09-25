#include"q2.h"
#include<iostream>
using namespace std;
int max=0;
struct firsec//record the longest length in every node and its son tree and the second longest
{
	int fir=0;
	int sec=0;
};
BTNODE<int>* findi(int i, BTNODE <int>&  r)//find data=i node in the tree of root r
{
	BTNODE<int>* p=NULL;
	if (&r != NULL) {
		if (r.a == i) return &r;
		else {

			p = findi(i, *(r.fch));
			if (p != NULL) { return p; }
			p = findi(i, *(r.nbr));
			if (p != NULL) return p;
		}
	}
	delete p;
	return NULL;
}
firsec backorder(BTNODE <int>&  r,firsec set,int *p)//meet every node in the tree and find the longest length in the tree
{
	BTNODE <int>*  t;
	int a, b;
	t = r.fch;
	if (t != NULL) 
	{
	  if(t->nbr==NULL){
		  set.fir = backorder(*t, set,p).fir + 1;
		  set.sec = backorder(*t, set,p).sec + 1;
		  if ((set.fir + set.sec) > max) max = set.fir + set.sec;
	  }
	  else if(t->nbr->nbr==NULL){
		  set.fir = backorder(*t, set,p).fir + backorder(*(t->nbr), set,p).fir + 2;
		  a = backorder(*t, set,p).fir + backorder(*(t->nbr), set,p).sec + 2;
		  b= backorder(*t, set,p).sec + backorder(*(t->nbr), set,p).fir + 2;
		  set.sec = a > b ? a : b;
		  if ((set.fir + set.sec) > max) max = set.fir + set.sec;
	  }
	  else {
		  int i = 0,j,temp;
		  while (t != NULL)
		  {
			  p[i] = backorder(*t, set, p).fir;
			  t = t->nbr;
			  i++;
		  }
		 
		  for (; p[i]!=-2; i++)
			  p[i] = -1;
		  
		  for (i = 0; i<2; i++)
			  for (j = i; p[j] >= 0; j++)
			  {
				  if (p[i] < p[j]) {
					  temp = p[i];
					  p[i] = p[j];
					  p[j] = temp;
				  }
			  }
		  set.fir = p[0];
		  set.sec = p[1];
		  if ((set.fir + set.sec) > max) max = set.fir + set.sec;
		  
	  }

	}	
	else { set.fir = 0; set.sec = 0; }
	return set;
	
}
int main()
{
	int i,n,a,b,*p;
	firsec set;
	cin >> n;
	p = new int[n];
	for (i = 0; i < n-1; i++)
		p[i] = -1;
	p[i] = -2;
	BTNODE <int> r,*t;
	r.a = 1;
	for (i = 0; i < n-1; i++)//build up the tree
	{
		cin >> a >> b;
		t = findi(a, r);
		if (t->fch == NULL)
			t->fch = new BTNODE <int>(b);
		else {
			t = t->fch;
			while (t->nbr != NULL)
				t = t->nbr;
			t->nbr= new BTNODE <int>(b);
		}
	}
	backorder(r,set,p);
	cout << max << endl;
	return 0;
}


