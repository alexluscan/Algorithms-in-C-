// OK
/*   
    Pictures - perimetrul figurii
	baleiere + arbori de intervale
 	Complexitate: O(N * lg MAXC) }
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


const int DIM = 20000; 
const int DIM_TREE = 4 * DIM; // ia si fii de pe nivelul urmator

ifstream fin("picture.in");
ofstream fout("pict.out");

struct Segm {
	int x, y1, y2, sgn;
};

struct Cmp {
	bool operator()(const Segm& a, const Segm& b)
	{
		return a.x < b.x || ( a.x == b.x && a.sgn < b.sgn );
	}
};

Segm V[DIM], H[DIM];
int Cnt[DIM_TREE], L[DIM_TREE];
int n, a, b, Val, k;

void Update(int nod, int l, int r);
void Read();
int Solve(Segm a[], int v);

int main()
{
	Read();
	cout << Solve(V, 1) + Solve(H, 1) << '\n';
	fin.close();
	fout.close();
	return 0;
}

int Solve(Segm s[], int v)
{
	int Perim = 0, temp = 0;
	sort(s, s + 2 * n, Cmp());
	for ( int i = 0; i < 2 * n; ++i )
	{
		a = s[i].y1, b = s[i].y2 - 1; Val = s[i].sgn; // in arbore: [a, b - 1]
		Update(1, -10001, 10001);

		Perim += abs(temp - L[1]);
		temp = L[1];
	}
	return Perim;
}

#define mid  ( (l + r) / 2 - ((l + r) % 2 && (l + r < 0)) )

void Update(int nod, int l, int r)
{
	if ( a <= l && r <= b )
		Cnt[nod] += Val;
	else
	{
		if ( a <= mid ) Update(2 * nod, l, mid);
		if ( b > mid ) Update(2 * nod + 1, mid + 1, r);
	}
	L[nod] = 0;
	if ( Cnt[nod] )
		L[nod] = r - l + 1;
	else
		if ( l < r ) // daca are fii
			L[nod] = L[2 * nod] + L[2 * nod + 1]; // sa nu treaca pe nivelul urmator in arbore, ca am incurcat-o cu memoria
}

void Read()
{
	int x1, y1, x2, y2;
	cin >> n;
	for ( int i = 0; i < n; ++i )
	{
		cin >> x1 >> y1 >> x2 >> y2;
		V[i].x = x1; V[i].y1 = y1; V[i].y2 = y2; V[i].sgn = -1;
		V[i + n].x = x2; V[i + n].y1 = y1; V[i + n].y2 = y2; V[i + n].sgn = 1;
		
		H[i].x = y1; H[i].y1 = x1; H[i].y2 = x2; H[i].sgn = -1;
		H[i + n].x = y2; H[i + n].y1 = x1; H[i + n].y2 = x2; H[i + n].sgn = 1; 
	}
}

