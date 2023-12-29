/*
    prof. Dan Pracsiu
    Stive
    Mediana - sortare quicksort
    Complexitate O(n)
*/
#include<fstream>
#include<algorithm>
#include <cstring>
using namespace std ;

char s[100002] ;
int n, k ,v;
int st[100001];

int SumaMax()
{
	int maxim, suma;
	maxim = st[k] ;
	suma = st[k] > 0 ? st[k] : 0;
	k-- ;
	while (st[k] != 1000)
	{
		suma += st[k] ;
		if (suma > maxim) maxim = suma;
		if (suma < 0) suma = 0 ;
		k-- ;
	}
	return maxim ;
}

int Mediana()
{
	int i, nr;
	i = k ;
	while (st[i] != 2000) i-- ;
	sort(st + i + 1, st + k + 1) ;
	nr = (k + i + 1) / 2 ;
	k = i ;
	return st[nr] ;
}

int main()
{
	int ii, semn, x ;
	ifstream fin("expresie.in") ;
	fin >> s ;
	n = strlen(s) ;
	fin.close() ;

	k = -1;
	for (ii=0 ; ii < n ; )
	{
		if (s[ii] == '(') { st[++k] = 1000; ii++; }
		else if (s[ii] == '[') {st[++k] = 2000 ; ii++ ;}
		else if (s[ii] == ')')
		{
			x = SumaMax() ;
			st[k] = x ;
			ii++ ;
		}
		else if (s[ii] == ']')
		{

			x = Mediana() ;
			st[k] = x ;
			ii++ ;
		}
		else if (s[ii] != ',') // e un numar
		{
			semn = 1;
			if (s[ii] == '-')
				{semn = -1; ii++;}
			x = 0 ;
			while (ii < n && '0' <= s[ii] && s[ii] <= '9')
			{
				x = x * 10 + (s[ii] - '0') ;
				ii++ ;
			}
			x = x * semn;
			st[++k] = x ;
		}
		else ii++ ,v++;
	}

	int suma = 0 ;
	for (ii=0 ; ii<=k ; ii++)
		suma += st[ii] ;

	ofstream fout("expresie.out") ;
	fout << v+1 << "\n";
	fout << suma << "\n";
	fout.close() ;
	return 0 ;
}
