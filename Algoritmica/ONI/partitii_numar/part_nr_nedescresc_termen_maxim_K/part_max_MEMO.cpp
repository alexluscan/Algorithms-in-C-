#include <fstream>
#include <iostream>
using namespace std;

// p[i][j] = nr partitii ale lui i cu cel mai mare termen, MAXIM j
const int N = 1000;
int p[N][N];


int Part(int n, int k)
{
    if (k == 0)  return 0;
    if (n == 0)  return 1;
    if (n < 0)   return 0;

    if (p[n][k]) return p[n][k];

    return p[n][k] = Part(n, k - 1) + Part(n - k, k);
}

int main()
{
	ifstream cin("part.in");
	ofstream cout("part.out");

    int n;
    int k;
    cin >> n >> k;
    
        
    cout << Part(n, k);

	return 0;
}
