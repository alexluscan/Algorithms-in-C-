#include <fstream>
using namespace std;

ifstream fin ("schi.in");
ofstream fout ("schi.out");

const int dim = 30005;
int n, q[dim], aib[dim], p[dim];

void Update(int p, int x);
int Query(int p);
int BS(int x);

int main()
{
	fin >> n;
	
	for (int i = 1; i <= n; ++i)
	{
		fin >> q[i];
		Update(i, 1);
	}
	
	for (int i = n; i >= 1; --i)
	{
		int loc = BS(q[i]); 
		p[loc] = i;
		Update(loc, -1);
	}
	
	for (int i = 1; i <= n; ++i)
		fout << p[i] << '\n';
}

void Update(int p, int x)
{
	for (int i = p; i <= n; i += i & -i)
		aib[i] += x;
}

int Query(int p)
{
	int sum = 0;
	for (int i = p; i >= 1; i -= i & -i)
		sum += aib[i];
		
	return sum;
}

int BS(int x)
{
	int st = 1, dr = n, m, t;
	
	int poz;
	while (st <= dr)
	{
		m = (st + dr) / 2;
		t = Query(m);
		if (t < x)
			st = m + 1;
		else if (t > x)
			dr = m - 1;
		else
		{
			poz = m;
			
			dr = m - 1;
		}
	}
	return poz;
}

