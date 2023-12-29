#include <fstream>
#include <iostream>
using namespace std;

ifstream fin("sumagauss2.in"); 
ofstream fout("sumagauss2.out"); 

int sp[200000], n;   // nr de termeni din sir

int BinarySearch(int v);

int main()
{
	int S;
	fin >> S;
	
	for (n = 1; n <= S; ++n)
	{
		sp[n] = n + sp[n - 1];
	
	}
	
	for (int i = 0; i < n; ++i)
	{
		int j = BinarySearch(sp[i] + S); 
	
		if (j != -1)
			fout << j << ' ' << i << '\n';
	}
	
	return 0;
}

int BinarySearch(int v)
{
	int l = 1, r = n, m;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (sp[m] == v)
			return m;
		if (v > sp[m])
			l = m + 1;
		else
			r = m - 1;
	} 
	
	return -1;
}
