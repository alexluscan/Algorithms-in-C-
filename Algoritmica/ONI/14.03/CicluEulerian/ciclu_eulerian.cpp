// OK
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
	
ifstream fin("ciclueuler.in");	
ofstream fout("ciclueuler.out");

const int NMAX = 100005, MMAX = 500005;
vector<int> G[NMAX];
bool usedEdge[MMAX];
int from[MMAX], to[MMAX]; 
vector<int> cycle;	

void DfsIter(int x);

int main() 
{	
    int n, m, x, y;	
    fin >> n >> m;
	
    for (int i = 0; i < m; ++i) 
    {
        fin >> x >> y;
        G[x].push_back(i);
        G[y].push_back(i);
        from[i] = x;
        to[i] = y;
    }
	bool eulerian = true;
	for (int i = 1; i <= n; ++i) 
		if (G[i].size() & 1) 
		{
			eulerian = false;
			break;
		}

	if (!eulerian)
		fout << "-1\n";
	else
	{
		DfsIter(1);
		
		for (size_t i = 0; i < cycle.size() - 1; ++i) 
			fout << cycle[i] << ' ';			
	}
    fout.close();
}

void DfsIter(int x)
{
	stack<int> stk;
		
	stk.push(1);
	while (!stk.empty()) 
	{
		x = stk.top();
	
		if (G[x].empty()) 
		{
			stk.pop();
			cycle.push_back(x);
			continue;
		}
		
		int e = G[x].back();
		G[x].pop_back();

		if (!usedEdge[e]) 
		{
			usedEdge[e] = true;
			int y = from[e] ^ to[e] ^ x;
			stk.push(y);
		}		 
	}
}
