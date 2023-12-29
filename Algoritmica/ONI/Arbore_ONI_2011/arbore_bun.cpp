#include <fstream>
#include <vector>
using namespace std;

const int  MOD  = 666013,
           MAXN = 100010;

int Nr[MAXN], Sol[MAXN];
vector<int> G[MAXN];
int N;
int F[MAXN], I[MAXN];

inline int Comb(int N, int K)
{
	if (N < K) return 0;
	if (N == K || K == 0) return 1;
	long long aux = 1;
	aux = (aux * F[N]) % MOD;
	aux = (aux * I[K]) % MOD;
	aux = (aux * I[N-K]) % MOD;
	return ( (int) aux);
}

void Df1(int nod, int tata)
{
	Nr[nod] = 1;
	for (int fiu : G[nod])
	{
		if (fiu == tata) continue;
		Df1(fiu, nod);
		Nr[nod] += Nr[fiu];
	}
}
void Df2(int nod, int tata)
{	
	int nr = 1;
	Sol[nod] = 0;
	long long aux = 1LL;
	for (int fiu : G[nod])
	{
		if (fiu == tata) continue;
		Df2(fiu, nod);
		aux = (((aux * Sol[fiu]) % MOD ) * Comb(Nr[nod] - nr, Nr[fiu])) % MOD;
		nr += Nr[fiu];
	}
	Sol[nod] = (int) aux;
}

int Pow(int a, int b) 
{
	if (b == 0) return 1;
	if (b == 1) return a;

	int temp = Pow(a, b >> 1);
	temp = (1LL * temp * temp) % MOD;
	if (b & 1) 	
		temp = (1LL *temp * a) % MOD;
	
	return temp;
}

void Precalc()
{
	F[0] = I[0] = 1;
	for (int i = 1; i <= N; ++i)
	{
		long long aux = 1LL * F[i-1];
		aux = (aux * i) % MOD;
		F[i] = (int) aux;
		I[i] = Pow(F[i], MOD-2);
	}
}

int main()
{
	ifstream fin("arbore.in");
	ofstream fout("arbore.out");
	
	fin >> N;	
	Precalc();
	
	for (int i = 1, x, y; i < N; ++i)
	{
		fin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	
	Df1(1, 0);
	Df2(1, 0);
	fout <<  Sol[1];
	
	return 0;
}
