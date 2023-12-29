// OK
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("horrible.in");
ofstream fout("horrible.ok");

#define N 100001
#define MAX 4*N + 1
#define inf 0x7fffffff


long long a[MAX], n;


int main() {
	int T, C, c, p, q, v;
	fin >> T;
	while (T-- )
	{
		memset(a, 0, sizeof(a));
		fin >> n >> C;
		while ( C--)
		{
			fin >> c >> p >> q;
			if ( c == 0 )
			{
				fin >> v;
				for (int i = p; i <= q; ++i )
                    a[i] += v;
			}
			else
			{
				long long sum = 0;
				for (int i = p; i <= q; ++i )
                    sum += a[i];
                fout << sum << '\n';
            }
		}
	}
	fin.close();
	fout.close();
	return 0;
}

