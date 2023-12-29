#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


FILE* fin  = fopen("sir.in", "r");
FILE* fout = fopen("sir.out", "w");

int n, Lmax;
void Get(int &x);

int a[100000];
int main()
{
	
	Get(n);
	fprintf(fout, "%d\n",  n);
	
	for (int i = 1; i <= n; ++i)
		Get(a[i]);

	for (int i = 1; i <= n; ++i)
		fprintf(fout, "%d ", a[i]);
	
    return 0;
}


const int Lim = 1 << 20;
int p =  Lim - 1;
char s[Lim];

void Next()
{
    if (++p == Lim)
        fread(s, 1, Lim, fin), p = 0;
}

void Get(int &x)
{
    for (; s[p] < '0' || s[p] > '9'; Next());
    
    for (x = 0; s[p] >= '0' && s[p] <= '9'; Next())
        x = x * 10 + s[p] - '0';
}
