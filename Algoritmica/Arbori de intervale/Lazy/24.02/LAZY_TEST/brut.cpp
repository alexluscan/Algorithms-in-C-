/**
 * Operation #1: Increment the elements within range [i, j] with value val
 * Operation #2: Get max element within range [i, j]
 */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define Dim 20000
#define inf 0x7fffffff

long long a[Dim], n, m;

void Update(int i, int j, int value) 
{
	for (int k = i; k <= j; ++k)
		a[k] += value;
}

long long QueryMax(int i, int j) 
{
	long long Max = -inf;
	for (int k = i; k <= j; ++k)
		Max = max(Max, a[k]);
	return Max;
}

ifstream fin("sir.in");
ofstream fout("brut.out");

int main() 
{
	fin >> n >> m;

	for (int i = 0; i < n; i++) 
		fin >> a[i];
	

	int op, i, j, val;
	while ( m--)
	{
		fin >> op >> i >> j;
		if ( op == 1 ) // update
		{
			fin >> val;
		//	cout << op << ' ' << i << ' ' << j; cin.get();
			Update(i, j, val);
		}
		
		else
			fout << QueryMax(i, j) << '\n';
	}
	fin.close();
	fout.close();
}

