#include <fstream>
# define MOD 31607
using namespace std;

ifstream in("drumuri.in");
ofstream out("drumuri.out");
int N,M,K,L,dp[255][255][255],S;

bool a[255][255];

int main()
{
	int i,j,k;
	in>>N>>M>>K>>L;
	while(M--)
	{
		in>>i>>j;
		a[i][j]=1;
	}
	dp[0][1][0]=1;
	for(i=1;i<=N;++i)
		for(j=1;j<=N;++j)
		{
			if(a[i][j])
				for(k=1;k<=K;++k)
					dp[i][j][k]=(dp[i-1][j][k-1]+dp[i][j-1][k-1])%MOD;
			else
				for(k=0;k<=K;++k)
					dp[i][j][k]=(dp[i-1][j][k]+dp[i][j-1][k])%MOD;
		}
	++L;
	if(L<=N)
		for(i=1;i<L;++i)
			S=(S+dp[i][L-i][K])%MOD;
	else
		for(i=L-N;i<=N;++i)
			S=(S+dp[i][L-i][K])%MOD;
	out<<S<<'\n';
	return 0;
}
