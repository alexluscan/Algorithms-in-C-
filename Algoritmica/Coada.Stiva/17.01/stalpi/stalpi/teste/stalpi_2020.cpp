#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>
using namespace std;

ifstream fin("stalpi.in");
ofstream fout("stalpi.out");

const int MaxN = 55, MaxD = 10005;
const int Inf = 0x3f3f3f3f;

int d[MaxN], n, e;
int ef[MaxN][MaxD];
deque<int> dq;

bool Check(int D);

int main()
{
	fin >> n >> e;
	for (int i = 2; i <= n; ++i)
		fin >> d[i];
	
	int st = 0, dr = MaxD, mij, sol;
	
	while (st <= dr)
	{
		mij = (st + dr) / 2;
		
		if (Check(mij))
			sol = mij, dr = mij - 1;
		else
			st = mij + 1;
		
	}
	
	fout << sol;
}

bool Check(int D)
{
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= d[n]; ++j)
			ef[i][j] = Inf;
		
	ef[1][0] = 0;

		
	for (int i = 2; i <= n; ++i)
	{
		dq.clear();
		for (int j = 0; j <= d[n]; ++j)
		{
			while (!dq.empty() && ef[i - 1][dq.back()] > ef[i - 1][j])
				dq.pop_back();
			dq.push_back(j);
	
			if (j - dq.front() > D)
				dq.pop_front();
			ef[i][j] =  ef[i - 1][dq.front()] + abs(j - d[i]);
		}	
	}
	
	for (int i = 1; i <= d[n]; ++i)
		if (ef[n - 1][i] <= e)
			return true;
	return false;
}
