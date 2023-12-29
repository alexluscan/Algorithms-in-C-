#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

int n, m, k;
int v[155], f[32770], d[155][32770];
vector <pair <int, int> > sol[32770];

void back (int x, int st, int nr)
{
	int i, v[20] = {0};
	
	for (i = 0; i < m; i ++)
		if (st & (1 << i))
			v[i] = 1;
	for (i = 0; i < m - 1; i ++)
		if (!v[i] && !v[i + 1] && !(x & (st ^ (3 << i))))
		{
			if (f[st ^ (3 << i)])
				continue;
			f[st ^ (3 << i)] = 1;
			
			sol[x].push_back (make_pair (st ^ (3 << i), nr + 1));
			back (x, st ^ (3 << i), nr + 1);
		}
}

inline int max (int a, int b) {return a > b ? a : b;}

int main ()
{
	freopen ("pavare.in", "r", stdin);
	freopen ("pavare.out", "w", stdout);
	
	scanf ("%d %d %d", &n, &m, &k);
	
	int i, j, st, x, y, lim = (1 << m) - 1, solf = 0;
	
	for (i = 0; i <= lim; i ++)
	{
		sol[i].push_back (make_pair (0, 0));
		//memset (f, 0, sizeof (f));
		for (vector <pair <int, int> > :: iterator it = sol[i - 1].begin(); it != sol[i - 1].end(); it ++)
			f[it -> first] = 0;
		back (i, 0, 0);
		//sort (sol[i].begin(), sol[i].end());
	}
	
	for (i = 1; i <= k; i ++)
	{
		scanf ("%d %d", &x, &y);
		v[x] ^= 1 << (m - y);
	}
	
	for (i = 1; i < n; i ++)
	{
		for (j = v[i]; j <= lim; j ++)
		{
			if ((j & v[i]) != v[i])
				continue;
			
			st = j | v[i + 1];
			for (vector <pair <int, int> > :: iterator it = sol[st].begin(); it != sol[st].end(); it ++)
			{
				x = v[i + 1] | it -> first;
				d[i + 1][x] = max (d[i + 1][x], d[i][j] + it -> second);
				solf = max (solf, d[i + 1][x]);
			}
		}
	}
	
	printf ("%d\n", solf);
	return 0;
}
