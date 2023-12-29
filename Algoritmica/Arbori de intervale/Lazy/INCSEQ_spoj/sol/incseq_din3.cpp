#include <iostream>
using namespace std;

const int mod = 5000000;
const int Dim = 100001;
int arb[55][500005], x, n, K, res;

void Update(int node, int st, int dr, int k, int pos, int val)
{
	if (st == dr)
	{
		arb[k][node] += val;
		return;
	}
	int mijl = (st + dr) / 2;
	
	if (pos <= mijl)Update(2 * node, st, mijl, k, pos, val);
	else Update(2 * node + 1, mijl + 1, dr, k, pos, val);
	
	arb[k][node] = arb[k][2 * node] + arb[k][2 * node + 1];
}

int Query(int node, int st, int dr, int k, int L, int R)
{
	if (L <= st && dr <= R)
		return arb[k][node];
	
	int mijl = (st + dr) / 2, s = 0;
	
	if (L <= mijl) 
		s += Query(2 * node, st, mijl, k, L, R);
	if (R > mijl) 
		s += Query(2 * node + 1, mijl + 1, dr, k, L, R);
	
	return s;
}

int main()
{
	cin >> n >> K;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x;
		Update(1, 1, Dim, 1, x, 1);
		for (int k = 2; k <= K; ++k)
			if (x > 1)
				Update(1, 1, Dim, k, x, Query(1, 1, Dim, k - 1, 1, x - 1));
	}
	cout << Query(1, 1, Dim, K, 1, Dim);
	return 0;
}

