// OK  ( e un pic mai lent decat puncte_ok.cpp )
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
int Nmax[262144], Cnt[262144];

void Read();
void Solve();
void Update(int nod, int l, int r);

void Scrie(vector<PII> v)
{
	for ( const auto& a : v)
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

		Res = max(Res, Nmax[1]);

		for ( ; j->first - i->first > W; ++i )
		{
			X = -1; L = i->second - H; R = i->second;
			Update(1, -40001, 40001);
		}
	}
}

void Update(int nod, int l, int r) 
{
	
  	if (Cnt[nod] != 0)  
  	{ 
   		Nmax[nod] += Cnt[nod]; 
		if (l != r) 
		{
			Cnt[2*nod]     += Cnt[nod]; 
    		Cnt[2*nod + 1] += Cnt[nod]; 
		}
   		Cnt[nod] = 0; 
  	}

	// Aici, nu pe prima linie!
	if (l > r || l > R || r < L) 
		return;

  	if (L <= l && r <= R)
  	{ 
    	Nmax[nod] += X;

		if (l != r)
		{ 
			Cnt[nod*2]  += X;
			Cnt[nod*2+1] += X;
		}
    	return;
	}
	
	Update(2*nod, l, mid);
	Update(2*nod + 1, mid + 1, r); 

	Nmax[nod] = max(Nmax[2*nod], Nmax[2*nod + 1]); 
}
