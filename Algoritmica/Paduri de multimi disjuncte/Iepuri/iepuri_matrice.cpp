#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream is("iepuri.in");
ofstream os("iepuri.out");

const int MOD = 30011;

vector<vector<int> > G;
int n, k;
vector<vector<int> >a;
int root;
vector<int> grad;

void Dfs(int nod);
void Read();

int main()
{
	Read();
	
	Dfs(root);
	int res = 0;
	for( int i = 1; i <= k; ++i )
	{
		res += a[root][i];
		if ( res > MOD)
			res -= MOD;
	}
					
	cout << res << '\n';
	
	is.close();
	os.close();
	return 0;
}

void Read()
{
	cin >> n >> k;
	G = vector<vector<int> >(n+1);
	a = vector<vector<int> >(n+1, vector<int>(k+1));
	grad = vector<int>(n+1);
	int b, c;
	for( int i = 1; i < n; ++i )
	{
		cin >> b >> c;
		G[b].push_back(c);
		++grad[c];
	}
	for(int i = 1; i <= n; ++i )
		if( !grad[i] )
		{
			root = i;
			break;
		}
	
}

void Dfs(int nod)
{
	a[nod].assign(k + 1, 1);
	for( const int& f : G[nod] )
	{
		Dfs(f);
		vector<int> Aux(k+1);
		
		for( int i = 1; i <= k; ++i )
			for( int j = i + 1; j <= k; ++j )
			{
				Aux[i] += (a[nod][i] * a[f][j]) % MOD;
				if( Aux[i] > MOD )
					Aux[i] -= MOD;
			}
		a[nod] = Aux;
	}
	
}




