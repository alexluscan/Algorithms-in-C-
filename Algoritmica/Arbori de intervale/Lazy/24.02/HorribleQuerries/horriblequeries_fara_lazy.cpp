// OK pe toate testele mele
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("horrible.in");
ofstream fout("horrible.ok");

#define N 100001
#define MAX 4*N + 5
#define inf 0x7fffffff

long long tree[MAX];
long long val[MAX], n;
int cnt;
void update(int x, int a, int b, int i, int j, int value)
{
//	if (a > j || b < i) return;
    cnt++;
  	if(a == b)
  	{
    	tree[x] += value;
    	return;
	}

	int m = a + (b - a ) / 2;
	if ( i <= m )update(2 * x, a, m, i, j, value);
	if ( j > m ) update(2 * x + 1, m + 1, b, i, j, value);

	tree[x] = tree[x*2] + tree[x*2+1];
}

long long  query(int x, int a, int b, int i, int j)
{
//	if ( a > j || b < i) return -inf;
    cnt++;
	if( i <= a && b <= j)
		return tree[x];
	int m = a + (b - a ) / 2;
	long long s1 = 0, s2 = 0;
	if ( i <= m )
		s1 = query(x*2, a, m, i, j);
	if ( j > m )
		s2 = query(2 * x + 1, m + 1, b, i, j);
	return s1 + s2;
}

int main() {
	int T, C, c, p, q, v;
	fin >> T;
	while (T-- )
	{
		memset(tree, 0, sizeof(tree));
		memset(val, 0, sizeof(val));
		fin >> n >> C;
		while ( C--)
		{
			fin >> c >> p >> q;
			if ( c == 0 )
			{
				fin >> v;
				update(1, 1, 40000, p, q, v);
			}
			else
				fout << query(1, 1, 40000, p, q) << '\n';

		}
	}

    fout << "cnt = " << cnt;
	fin.close();
	fout.close();
	return 0;
}

