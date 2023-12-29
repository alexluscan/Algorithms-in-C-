#include <vector>
using namespace std;

#define MAX_N 13
#define Inf 2000


class CollectingMarbles
{
public:

	int mostMarbles(vector <int> w, int capBag, int nrBags)
	{
		int dp[1 << MAX_N]; // dp[mask] = nr minim de saci folosit pentru depozitarea elementelor din mask
		int N = w.size();
		
		for (int i = 0; i < 1 << N; ++i) 
			dp[i] = Inf;
		
		dp[0] = 0;
		
		for (int mask = 0; mask < 1 << N; ++mask) // pt fiecare multime (masca) de obiecte care sa-mi umple un singur rucsac
		{
			int sum = 0;                       // calculam gretatea acestei submultimi de obiecte
			for (int i = 0; i < N; ++i)
				if (mask & (1 << i))
					sum += w[i];
		    // daca obiectele din masca mask incap intr-un singur sac
			if(sum <= capBag)
			{
				for (int i = 0; i < 1 << N; ++i)      // pt fiecare submultime i de obiecte, disjuncte de cele din mask
					if(!(i & mask) && dp[i] < nrBags) // si care nu umple toti sacii
						dp[i | mask] = min(dp[i | mask], dp[i] + 1); // obiectele din mask merg intr-un sac, iar cele din submultimea i in dp[i] saci
			}
        }

		int ret = 0;
	    for (int mask = 0; mask < 1 << N; mask++)
		    if(dp[mask] <= nrBags)                          // dintre toate submultimile care incap in maximum nrBags saci
			    ret = max(ret,  __builtin_popcount(mask));  // aleg submultimea cu numar maxim de biti (de obiecte)

		return ret;
  }
};

int main()
{

}
