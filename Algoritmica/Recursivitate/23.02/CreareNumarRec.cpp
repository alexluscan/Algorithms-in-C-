#include <iostream>
#include <cstring>
using namespace std;

void F(int n, int a[], int& k) // numarul de elemente 
{
	
	if (n == 0)
	{
		k = -1;
		return;
	}
	F(n - 1, a, k);
	
	if (a[n - 1] % 2 == 0)
	{
		if (k == -1)
			k = 0;
		k = k * 10 + a[n - 1];
	}
}

int main()
{
	int a[] = {2, 3, 5, 6, 4, 1};
	int n = 6, k;
	F(n, a, k);
	cout << k;
}
