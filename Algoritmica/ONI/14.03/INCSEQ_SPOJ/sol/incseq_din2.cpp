#include <iostream>
using namespace std;
const int mod = 5000000;
const int Dim = 100001;
int aib[55][100005], x, n, K, res;

inline void Update(int k, int poz, int val)
{
	for (int i = poz; i <= Dim; i += i & -i)
	{
		aib[k][i] += val;
		if (aib[k][i] > mod)
			aib[k][i] -= mod;
	}
}

inline int Query(int k, int poz)
{
	int s = 0;
	for (int i = poz; i > 0; i -= i & -i)
	{
		s += aib[k][i];
		if (s > mod)
			s -= mod;
	}
	return s;
}

int main()
{
	cin >> n >> K;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x;
		Update(1, x, 1);
		for (int k = 2; k <= K; ++k)
			Update(k, x, Query(k - 1, x - 1));
	}
	cout << Query(K, Dim);
	return 0;
}

