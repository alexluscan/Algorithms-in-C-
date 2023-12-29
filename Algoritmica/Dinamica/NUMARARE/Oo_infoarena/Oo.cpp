// https://infoarena.ro/problema/oo
// O(n)
#include <fstream>
#include <algorithm>
using namespace std;
 
ifstream fin("oo.in");
ofstream fout("oo.out");
 
/**
dp[i] = suma maxima obtinuta din a[1], ..., a[i], alegand
          obligatoriu pe a[1]+a[2]
- aleg val. maxima
dp[i] = suma maxima obtinuta din a[1], ..., a[i], alegand
          obligatoriu pe a[2]+a[3]
- aleg val. maxima
dp[i] = suma maxima obtinuta din a[1], ..., a[i], alegand
          obligatoriu pe a[1]+a[n]
- aleg val. maxima
*/
int a[100003], n, dp[100003];
 
int main()
{
    int i, M;
    fin >> n;
    for (i = 1; i <= n; i++)
        fin >> a[i];
    /// alegand obligatoriu pe a[1]+a[2]
    dp[1] = 0;
    dp[2] = a[1] + a[2];
    dp[3] = dp[4] = dp[2];
    for (i = 5; i < n; i++)
        dp[i] = max(dp[i - 1], a[i] + a[i - 1] + dp[i - 3]);
    M = dp[n - 1];
 
    /// alegand obligatoriu pe a[2]+a[3]
    dp[1] = dp[2] = 0;
    dp[5] = dp[4] = dp[3] = a[2] + a[3];
    for (i = 6; i <= n; i++)
        dp[i] = max(dp[i - 1], a[i] + a[i - 1] + dp[i - 3]);
    M = max(M, dp[n]);
 
    /// alegand obligatoriu pe a[1]+a[n]
    dp[1] = a[n] + a[1];
    dp[2] = dp[3] = dp[1];
    for (i = 4; i <= n - 2; i++)
        dp[i] = max(dp[i - 1], a[i] + a[i - 1] + dp[i - 3]);
    M = max(M, dp[n - 2]);
 
    fout << M << "\n";
    
    fout.close();
    fin.close();
    return 0;
}
