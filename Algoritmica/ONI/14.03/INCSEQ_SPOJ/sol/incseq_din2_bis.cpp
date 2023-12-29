#include <iostream>
using namespace std;
const int mod = 5000000;
const int Dim = 100001;
int aib[55][100005], x, n, K, res;

inline void Update(int b[], int poz, int val)
{
	for (int i = poz; i <= Dim; i += i & -i)
	{
		b[i] += val;
		if (b[i] > mod)
			b[i] -= mod;
	}
}

inline int Query(int b[], int poz)
{
	int s = 0;
	for (int i = poz; i > 0; i -= i & -i)
	{
		s += b[i];
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
		Update(aib[1], x, 1);
		for (int k = 2; k <= K; ++k)
			Update(aib[k], x, Query(aib[k - 1], x - 1));
	}
	
	cout << Query(aib[K], Dim);
	return 0;
}

