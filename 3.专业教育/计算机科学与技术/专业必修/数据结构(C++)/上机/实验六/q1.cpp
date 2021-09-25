#include"text.h"
#include<iostream>
using namespace std;
static int m = 0;
void towers(int n, int A, int B, int C) {
	LStack<int> s;
	int done = 0; int temp;
	while (!done) {
		while (n>1) {
			//s_tack(n, A, B, C, &s);
			{
				s.push(n);
				s.push(A);
				s.push(B);
				s.push(C);
			}
			//setvar1(&n, &A, &B, &C);
			{

				n--;
				temp = B;
				B = C;
				C = temp;
			}

		}
		// printf(¡°\n %d -> %d\n¡±, A, C);
		// cout << A << "->" << C << endl;
		m++;
		if (!s.empty()) {
			// restore(&n, &A, &B, &C, &s);
			{
				s.pop(&C);
				s.pop(&B);
				s.pop(&A);
				s.pop(&n);
			}
			// printf(¡°\n %d -> %d\n¡±, A, C);
			// cout << A << "->" << C << endl;
			m++;
			//setvar2(&n, &A, &B, &C);
			{
				n--;
				temp = B;
				B = A;
				A = temp;
			}

		}
		else done = 1;

	}

}
int main()
{
	int n;
	cin >> n;
	towers(n, 1, 2, 3);
	cout << m << endl;
	return 0;
}

