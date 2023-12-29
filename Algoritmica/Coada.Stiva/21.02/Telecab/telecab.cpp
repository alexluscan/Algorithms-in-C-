/*	100 puncte
 *  Recursie cu memoizare 
 *  Complexitate O(n + K*S)
 *  Constantin Galatan
 */ 
#include <fstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define INF 0x3f3f3f3f
ifstream fin("telecab.in");
ofstream fout("telecab.out");

const int MAXN = 100005;
int n, h[MAXN], poz[MAXN], st[MAXN];
int S, K; // Suma si cota care trebuie atinsa sau depasita
int k;
int tmin[1001][1001];
int cnt;
int Dist(int i, int j);
int Timp(int i, int s);

int main()
{
	fin >> n >> K >> S;
	memset(poz, -1, sizeof(poz));
    for (int i = 0; i < n; i++)
    {
		fin >> h[i];
        while (k > 0 && h[i] > h[st[k - 1]])
            poz[st[--k]] = i;

        st[k++] = i;
    }
	long long d = 0;
    for (int i = 0; i < n - 1; )
    {
        if ( poz[i] > 0 ) // exista o cota mai inalta, atunci - legatura directa
        {
			d += Dist(poz[i], i);
			i = poz[i];
		}
		else
		{
			if ( h[i] > h[i+1] ) // cobor
				d += Dist(i, i + 1);
			else
				d++;   // orizontala
			i++;
		}
	}
	for( int i = 0; i <= 1000; ++i)
		for( int j = 0 ; j <= 1000; ++j)
			tmin[i][j] = INF;
	fout << d << '\n';
	fout << Timp(0, S) << '\n';

	fin.close();
	fout.close();

    return 0;
}

int Dist(int i, int j)  // distanta de la varful i la j
{
	int a = h[i] - h[j], b = j - i;
	return (int)sqrt(double(a * a  + b * b));
}

// Timpul minim necesar ca sa atinga CEL PUTIN cota K, stind ca are suma initiala S
int Timp(int i, int s) // timpul minim necesar sa ajung la final incepand de la poz i cu suma s
{
	if ( s < 0 ) return -1; 

	int& ret = tmin[i][s];
	if ( i >= K - 1 ) return ret = 0;
	if ( ret != INF ) return ret;  // timpul a fost calculat anterior

	if ( poz[i] > 0 ) // am in dreapta o cota mai inalta
	{
		int r = Timp(poz[i], s - (h[poz[i]] - h[i]));
		if ( r == -1 ) return ret = -1;
		return ret = Dist(i, poz[i]) + r;
	}
	// cobor
	if ( h[i+1] < h[i] )
	{
		int t1 = Timp(i + 1, s - (h[i] - h[i+1]));
		t1 = (t1 == -1) ? INF : 1 + t1; // cobor o ora dar platesc

		int t2 = Timp(i + 1, s);     // cobor cu viteza v, costa timp, dar nu platesc
		t2 = (t2 == -1) ? INF : Dist(i, i + 1) + t2;
		ret = min(t1, t2);
		if ( ret == INF )
			ret = -1;
		return ret;
	}
	// inaltimi egale
	int t = Timp(i + 1, s);
	if ( t == -1 ) return ret = -1;
	return ret = 1 + t;
}
