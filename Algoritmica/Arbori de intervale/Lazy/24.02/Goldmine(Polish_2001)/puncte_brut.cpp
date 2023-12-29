// OK
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define mid ((l+r)/2 - ((l+r)%2 && (l+r) < 0))

ifstream fin("puncte.in");
ofstream fout("puncte.out");

typedef pair<int, int> PII;
vector<PII> p;
typedef vector<PII>::iterator IT;

int H, W, n;     // inaltime, latime 
int X, L, R;     // X = 1 daca intervalul se adauga in arbore capetele intervalului de interogare
int Res;
int Max[262144], Val[262144];

void Read();
void Solve();
void Update(int nod, int l, int r);

void Scrie(vector<PII> v)
{
	for ( auto a : v)
		fout << a.first << ' ' << a.second << '\n';
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
		cin >> p[i].first >> p[i].second;
}

void Solve()        // doua linii de baleiere: i si j
{
	for ( IT i = p.begin(), j = p.begin(); j != p.end();  )
	{
		for ( ; j != p.end() and j->first - i->first <= W; ++j ) 
		{
			X = 1; L = j->second - H; R = j->second;
			Update(1, -40001, 40001);
		}		
		
		Res = max(Res, Max[1]);

		for ( ; j->first - i->first > W; ++i )
		{
			X = -1; L = i->second - H; R = i->second; 
			Update(1, -40001, 40001); 
		}
	}
}

void Update(int nod, int l, int r)
{
	if ( l == r )
	{
		Max[nod] += X;
		return;
	}
	if ( L <= mid ) Update(2 * nod, l, mid);
	if ( R > mid ) Update(2*nod + 1, mid + 1, r);
	Max[nod] = max(Max[2*nod], Max[2*nod + 1]);
}
