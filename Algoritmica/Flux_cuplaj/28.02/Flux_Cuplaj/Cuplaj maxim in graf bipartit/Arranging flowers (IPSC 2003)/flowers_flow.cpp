#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

ifstream is("a2.in");
ofstream os("flowers.out");

using VI = vector<int>;
using VVI = vector<VI>;

int n, m, test;
bitset<405> ok;
VI t, aux;
VVI g, c, answ;

void Read();
void Write();
bool MaxFlow();
bool Bfs();

int main()
{
	is >> test;
	while ( test-- )
	{
		Read();
		t = VI(2 * m + 2, -1);
		while ( MaxFlow() )
		{
			aux.clear();
			for ( int j = m + 1; j <= 2 * m; ++j )
				for ( const auto &i : g[j] )
					if ( i <= m && c[j][i] )
					{
						aux.push_back(i);
						c[j][i] = 0;
					}
			answ.push_back(aux);
			for ( int i = 1; i <= m; ++i )
			{
				c[0][i] = c[m + i][2 * m + 1] = 1;
				c[i][0] = c[2 * m + 1][m + i] = 0;
			}
		}
		Write();
	}
	is.close();
	os.close();
	return 0;
}

bool MaxFlow()
{
	int flux = 0, flow;
	while ( Bfs() )
		for ( const auto &nodv : g[2 * m + 1] )
		{
			if ( !ok[nodv] || c[nodv][2 * m + 1] <= 0 )
				continue;
			t[2 * m + 1] = nodv;
			flow = 0x3f3f3f3f;
			for ( int x = 2 * m + 1; x; x = t[x] )
				flow = min(flow, c[t[x]][x]);
			if ( flow == 0x3f3f3f3f )
				continue;
			flux += flow;
			for ( int x = 2 * m + 1; x; x = t[x] )
			{
				c[t[x]][x] -= flow;
				c[x][t[x]] += flow;
			}
		}
	return flux == m;
}

void Write()
{
	os << answ.size() << "\n";
	for ( const auto &i : answ )
	{
		for ( const auto &j : i )
			os << j << " ";
		os << "\n";
	}
	os << "\n";
	answ.clear();
}

bool Bfs()
{
	ok.reset();
	t.assign(2 * m + 2, -1);
	queue<int> q;
	ok[0] = 1;
	q.push(0);
	int nod;
	while ( !q.empty() )
	{
		nod = q.front();
		q.pop();
		if ( nod == 2 * m + 1 )
			continue;
		for ( const auto &nodv : g[nod] )
			if ( !ok[nodv] && c[nod][nodv] > 0 )
			{
				ok[nodv] = 1;
				t[nodv] = nod;
				q.push(nodv);
			}
	}
	return ok[2 * m + 1];
}

void Read()
{
	is >> m >> n;
	g.resize(2 * m + 2);
	c = VVI(2 * m + 2, VI(2 * m + 2));
	for ( int i = 1; i <= m; ++i )
	{
		c[0][i] = 1;
		c[m + i][2 * m + 1] = 1;
		g[0].push_back(i);
		g[i].push_back(0);
		g[m + i].push_back(2 * m + 1);
		g[2 * m + 1].push_back(m + i);
	}
	for ( int i = 1; i <= m; ++i )
		for ( int j = m + 1; j <= 2 * m; ++j )
			c[i][j] = 1;
	int n1;
	for ( int i = 1; i <= n; ++i )
		for ( int j = 1; j <= m; ++j )
		{
			is >> n1;
			c[n1][m + j] = 0;
		}
	for ( int i = 1; i <= m; ++i )
		for ( int j = m + 1; j <= 2 * m; ++j )
			if ( c[i][j] )
			{
				g[i].push_back(j);
				g[j].push_back(i);
			}
}
