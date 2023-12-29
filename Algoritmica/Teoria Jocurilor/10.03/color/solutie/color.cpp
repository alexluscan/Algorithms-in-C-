#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
 
ifstream fin("color2.in");
ofstream fout("color2.out");
 
const int MAXN = 16005;
 
vector<int> T[MAXN], sol;
int fth[MAXN], bth[MAXN], s[MAXN];
bool up[MAXN], down[MAXN];
 
void dfs_down(int u, int prv) 
{
	int son[2], p = 0;
	down[u] = true;
	for (int v : T[u]) 
	{
		if ( v != prv ) 
		{
		  dfs_down( v, u );
		  son[p++] = v;
		}
	}
	if ( !p ) return; // n-are fii
	down[u] = (down[son[0]] ^ 1) & (down[son[1]] ^ 1);
}
 
void dfs_up(int u, int prv) 
{
	up[u] = ((down[bth[u]]) | (up[fth[u]] ^ 1));
	for (int v : T[u]) 
		if (v != prv) 
		  dfs_up( v, u );	
}
 
int main() 
{
	int n, u, v;

	fin >> n;
	for ( int i = 1; i < n; ++i ) 
	{
		fin >> u >> v;
		T[u].push_back(v);
		T[v].push_back(u);
		fth[v] = u;
		if ( s[u] != 0 ) 
		{
		  bth[s[u]] = v; // brother[s[u]] = v
		  bth[v] = s[u];
		} 
		else 
		  s[u] = v; // son[u] = v
	}
  
	dfs_down(1, 0);
	dfs_up(1, 0);
	
	for (int i = 1; i <= n; ++i) 
		if (up[i] & down[i]) 
			sol.push_back(i);

	fout << sol.size() << "\n"; 
	for (int i = 0; i < sol.size(); ++i) 
		fout << sol[i] << " ";

	return 0;
}
