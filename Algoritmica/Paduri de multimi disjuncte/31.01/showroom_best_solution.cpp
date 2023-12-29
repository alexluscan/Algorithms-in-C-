#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
using namespace std;

ifstream fin("showroom.in");
ofstream fout("showroom.out");

const int N = 505, Dim = 50005;
const int Mod = 9001;
int root[N], n, k, a, r, d;
int fact[N], inv[N];
string s, t;

vector<int> v[N];
unordered_map<string, int> mp;

int Find(int x)
{
	if (x == root[x])
		return x;
	return root[x] = Find(root[x]);
}

void Union(int x, int y)
{
	int r1 = Find(x);
	int r2 = Find(y);
	if (r1 != r2)
		root[min(r1, r2)] = root[max(r1, r2)];
}

int main()
{
	ios_base::sync_with_stdio(false);
	fin.tie(0);
	fout.tie(0);
	
	fin >> n >> a >> r >> k;
	fin.get();
	
	istreamstring is;
	
	for (int i = 1; i <= n; ++i)
	{
		getline(fin, t);
		is.str(t);
		
		while (is >> s)
		{
			if (mp[s] == s.end())
				mp[s] = ++d;
			v[i].push_back(mp[s]);
		}
	}
	for (int i = 1; i <= d; ++i)
		root[i] = i;
	fact[0] = inv[0] = 1;
	for (int i = 1; i < Dim; ++i)
	{	
		fact[i] = (fact[i - 1] * i) % Mod;
		inv[i] = Pow(fact[i], Mod - 2);
	}
	for (int i = 1; i <= n; ++i)
	{
		for (const int& x : v[i])
		{
			
		}
	}
}


