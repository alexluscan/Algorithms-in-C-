#include <vector>
using namespace std;

#define MAX_N 13
#define MAX 2000
#define f(i, n)   for(int i = 0; i < n; i++)
int dp[1 << MAX_N];



int mostMarbles(vector <int> w, int capBag, int nrBags)
{
	int N = w.size();
	int ret = 0;

	// dp[mask] = nr minim de saci folosit pentru depozitarea elementelor din mask
	f(i, 1 << N) dp[i] = MAX;
	
	dp[0] = 0;
	f(mask, 1 << N) // pt fiecare multime (masca) de obiecte care sa-mi umple un singur rucsac
	{
		int sum = 0;
		f(i, N)
			if(mask & (1 << i))
				sum += w[i];
		// daca obiectele din masca mask incap intr-un singur sac
		if(sum <= capBag)
		{
			f(i, 1 << N)  // pt fiecare submultime i de obiecte care nu umple toti rucsacii
				if(!(i & mask) && dp[i] < nrBags)
					dp[i | mask] = min(dp[i | mask], dp[i] + 1); // obiectele din mask merg intr-un sac, iar cele din submultimea i in dp[i] saci
		}
	}

  f(mask, 1 << N)
	if(dp[mask] <= nrBags)
		ret = max(ret,  __builtin_popcount(mask));

return ret;
}

int main()
{

}
