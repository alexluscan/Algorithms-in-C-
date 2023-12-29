// OK !    dar WA pe SPOJ
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("horrible.in");
ofstream fout("horrible.out");

#define N 100001
#define MAX 4*N + 5
#define inf 0x7fffffff

long long tree[MAX];
long long val[MAX], n;

void update(int x, int a, int b, int i, int j, long long value)
{
  	if (val[x] != 0)
  	{
   		tree[x] += (b - a + 1) * val[x];

		if (a != b)
		{
			val[2*x]   += val[x];
    		val[2*x+1] += val[x];
		}
   		val[x] = 0;
  	}

    if(a > b || a > j || b < i)
        return; // ok ( si fara if la update) ok (aici, nu sus)
  	if (i <= a && b <= j)
  	{
    	tree[x] += (b - a + 1) * value;

		if (a != b)
		{
			val[2*x]   += value;
			val[2*x+1] += value;
		}
    	return;
	}

	int m = a + (b - a ) / 2;
//	if ( i <= m )
	update(2 * x, a, m, i, j, value);
//	if ( j > m  )
	update(2 * x + 1, m + 1, b, i, j, value);

	tree[x] = tree[x*2] + tree[x*2+1];
}

long long  query(int x, int a, int b, int i, int j)
{
	if (val[x] != 0)
	{
		tree[x] += (b - a + 1) * val[x];
		if(a != b)
		{
			val[2*x]   += val[x];
			val[2*x+1] += val[x];
		}
		val[x] = 0;
	}

	if ( i <= a && b <= j)
		return tree[x];
	if(a > b || a > j || b < i) return 0; // ok (aici, nu sus)

	int m = a + (b - a ) / 2;
	long long s1 = 0, s2 = 0;
//	if ( i <= m )
		s1 = query(2*x, a, m, i, j);
//	if ( j > m ) // nu merge cu if-uri
		s2 = query(2*x + 1, m + 1, b, i, j);
	return s1 + s2;
}

int main()
{
	int T, C, c, p, q;
	long long v;
	fin >> T;
	while ( T-- )
	{
		memset(tree, 0, sizeof(tree));
		memset(val,  0, sizeof(val));
		fin >> n >> C;
		while ( C--)
		{
			fin >> c >> p >> q;
			if ( c == 0 )
			{
				fin >> v;
				update(1, 1, 100001, p, q, v);
			}
			else
				fout << query(1, 1, 100001, p, q) << '\n';
		}
	}
	fin.close();
	fout.close();
	return 0;
}

