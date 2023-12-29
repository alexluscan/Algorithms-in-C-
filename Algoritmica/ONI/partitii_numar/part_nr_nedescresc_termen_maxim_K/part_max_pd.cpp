#include <fstream>
#include <iostream>
using namespace std;


// p[i][j] = nr partitii ale lui i cu cel mai mare termen, MAXIM j
const int N = 1000;
int p[N][N];

int main()
{
	ifstream cin("part.in");
	ofstream cout("part.out");

    int n;
    int k;
    cin >> n >> k;
    
   // initializari
    for (int i = 0; i <= n; i++)
        p[i][0] = 0;
        
    for (int i = 1; i <= k; ++i)
        p[0][i] = 1;
	
	 for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)  
            if (i - j < 0)
                p[i][j] = p[i][j - 1];
            else
				p[i][j] = p[i][j - 1] + p[i - j][j];
        
    cout << p[n][k];

	return 0;
}
