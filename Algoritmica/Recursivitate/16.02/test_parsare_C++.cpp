#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


ifstream fin("sir.in");
ofstream fout("sir.out");

int n, Lmax;
void Get(int &x);

int a[100000];

int main()
{
	
	Get(n);
	fout << n << '\n';
	
	for (int i = 1; i <= n; ++i)
		Get(a[i]);

	for (int i = 1; i <= n; ++i)
		fout << a[i] << ' ';
	
    return 0;
}

const int Lim = 10;
int p =  Lim - 1;
char s[Lim];

void Next()
{
    if (++p == Lim)
        fin.get(s, Lim + 1, EOF), p = 0;
}

void Get(int &x)
{
	int sgn = 1;
    for (; s[p] < '0' || s[p] > '9'; Next())
		if (s[p] == '-')
			sgn = -1;
    
    for (x = 0; s[p] >= '0' && s[p] <= '9'; Next())
        x = x * 10 + s[p] - '0';
    x *= sgn;
}
