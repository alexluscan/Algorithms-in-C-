// OK
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

// Nmax[1] - Nr maxim de segmente vericale care se suprapun 

#define mid ((l+r)/2 - ((l+r)%2 && (l+r) < 0))
#define x first
#define y second

ifstream fin("puncte.in");
ofstream fout("puncte.out");

typedef pair<int, int> PII;
vector<PII> p;
typedef vector<PII>::iterator IT;

int H, W, n;     // inaltime, latime
int X, L, R;     // X = 1 daca intervalul se adauga in arbore capetele intervalului de interogare
int Res;
int Nmax[262144], Cnt[262144];

void Read();
void Solve();
void Update(int nod, int l, int r);

void Scrie(vector<PII> v)
{
	for ( auto a : v)
		fout << a.x << ' ' << a.y << '\n';
	fout << '\n';
}

int main()
{
	Read();
	sort(p.begin(), p.end());
//	Scrie(p);
	Solve();
	cout << Res << '\n';
	fin.close();
	fout.close();

	return 0;
}

void Read()
{
	cin >> W >> H >> n;
	p.resize(n);
	for ( int i = 0; i < n; ++i )
		cin >> p[i].x >> p[i].y;
}

void Solve()        // doua linii de baleiere: i si j
{
	for ( IT i = p.begin(), j = p.begin(); j != p.end();  )
	{
		for ( ; j != p.end() and j->x - i->x <= W; ++j )
		{
			X = 1; L = j->y - H; R = j->y;
			Update(1, -40001, 40001);
		}

		Res = max(Res, Nmax[1]);

		for ( ; j->x - i->x > W; ++i )
		{
			X = -1; L = i->y - H; R = i->y;
			Update(1, -40001, 40001);
		}
	}
}

void Update(int nod, int l, int r)
{
	if ( L <= l && r <= R )
	{
		Cnt[nod] += X;  // we're lazy
		Nmax[nod] += X;
		return;         // don't bother to update the children 
	}
	
	// we can't be lazy any longer 
	if ( l != r )
	{                               // push down
		Cnt[2*nod]     +=  Cnt[nod];         
		Cnt[2*nod + 1] +=  Cnt[nod];
		Nmax[2*nod] += Cnt[nod];
		Nmax[2*nod + 1] += Cnt[nod];
		Cnt[nod] = 0;
	}

	if ( L <= mid ) Update(2 * nod, l, mid);
	if ( R > mid )  Update(2 * nod + 1, mid + 1, r);

	if ( l != r)
		Nmax[nod] = max(Nmax[2*nod], Nmax[2*nod + 1]);
}
