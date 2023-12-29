#include <fstream>
#include <algorithm>
#include <deque>

using namespace std;

#define in_file "stalpi2.in"
#define out_file "stalpi2.out"

const int INF = 1000000000;

void read();
void write();
void doit();
bool test( int x );
inline int nat( int x )
{
	return x < 0 ? ( -1 ) * x : x;
}

int n, e, max_d, max_dist;
int dist[55];
int a[55][10005];
deque<int> d;

int main()
{
	read();
	doit();
	write();
	return 0;
}

void read()
{
	ifstream fin( in_file );
	fin >> n >> e;
	for ( int i = 2; i <= n; ++i )
		fin >> dist[i];
	max_dist = dist[n];
	fin.close();
}

void write()
{
	ofstream fout( out_file );
	fout << max_d;
	fout.close();
}

void doit()
{
	int l1 = 0, l2 = max_dist;
	while ( l1 <= l2 )
	{
		int mj = ( l1 + l2 ) / 2;
		if ( test( mj ) )
		{
			max_d = mj;
			l2 = mj - 1;
		}
		else
			l1 = mj + 1;
	}
}

bool test( int x )
{
	int i, j;
	for ( i = 1; i <= n; ++i )
		for ( j = 0; j <= max_dist; ++j )
			a[i][j] = INF;
	a[1][0] = 0;

	for ( i = 2; i < n; ++i )
	{
		d.clear();
		for ( j = 0; j <= max_dist; ++j )
		{
			while (!d.empty() && a[i - 1][j] < a[i - 1][d.front()]) d.pop_front();
			d.push_front(j);
			while (!d.empty() && d.back() < j - x) d.pop_back();

			if (!d.empty())
				a[i][j] = min( a[i][j], a[i - 1][d.back()] + nat( dist[i] - j ) );
		}
	}

	for ( i = max_dist; i >= max( 1, max_dist - x ); --i )
		if ( a[n - 1][i] <= e )
			return true;

	return false;
}

