#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream is("iepuri.in");
ofstream os("iepuri.out");

const int MOD = 30011;
using VI = vector<int>;

vector<VI> G;
int n, k;
VI grad;
int root;

VI Dfs(int nod);
void Read();

int main()
{
	Read();
	
	VI res = Dfs(root);
	int r = 0;
	for( int i = 1; i <= k; ++i )
	{
		r += res[i];
		if( r > MOD )
			r -= MOD;
	}
	
					
	cout << r << '\n';
	
	is.close();
	os.close();
	return 0;
}

void Read()
{
	cin >> n >> k;
	G = vector<VI>(n+1);
	grad = VI(n+1);
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

VI Dfs(int nod)
{
	VI rn(k + 1, 1);
	for( const int& f : G[nod] )
	{
		VI rf = Dfs(f);
		VI Aux(k+1);
		
		for( int i = 1; i <= k; ++i )
			for( int j = i + 1; j <= k; ++j )
			{
				Aux[i] += (rn[i] * rf[j]) % MOD;
				if( Aux[i] > MOD )
					Aux[i] -= MOD;
			}
		rn = Aux;
	}
	return rn;
}




