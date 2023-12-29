// ok
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
#define MOD 30011

typedef vector<int> VI;
vector<VI> G;
VI fa;
//ofstream fout("iepuri.out");

int n, K, root;
void Read();
VI DF(int nod);

int main()
{
	Read();
	
	VI S = DF(root);
	

	cout << S[K] << '\n';
	
//	fout.close();
}

VI DF(int x)
{
	VI rx(K + 1, 1); // sx[i] nr posibilitati de a avea in x EXACT i morcovi
	VI sx(K + 1, 0); // sx[i] nr posibilitati de a avea in x cel mult i morcovi
	
	
	for (const int& son : G[x])
	{
		VI sf = DF(son);
		for ( int i = 1; i <= K; ++i )   // citi are nod
		{
			int dif = sf[K] - sf[i]; // nr posib. de a avea in fiu cel putin i + 1 morcovi
			if (dif < 0)
				dif += MOD;
			rx[i] =  (dif * rx[i]) % MOD;
		}
		
	}
	
	for (int i = 1; i <= K; ++i)
		sx[i] = (sx[i - 1] + rx[i]) % MOD;
	
	return sx;
}


void Read()
{
	//ifstream fin("iepuri.in");
	cin >> n >> K;
	G.resize(n + 1); fa.resize(n + 1);
	int father, son;
	for ( int i = 1; i < n; ++i )
	{
		cin >> father >> son;
		fa[son] = father;
		G[father].push_back(son);
	}
	
	for ( int i = 1; i <= n; ++i )
		if (fa[i] == 0 )
		{
			root = i;
			break;
		}
	
	//fin.close();
}
