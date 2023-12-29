#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define MAXN 200100

char S[100];
int A[MAXN];
int N, K, i, Left, Right, Mid, Sol, Poz, sign;

inline bool Check(int Rez)
{
	int Last = -2000000000;
	int Nr = 0;

	for (int i = 1; i <= N; ++i){
		if (A[i] <= Last)
			continue;
		Last = A[i] + Rez;
		++Nr;
		if (Nr > K) break;
	}
	return (Nr <= K);
}

int main()
{
	freopen("2d.in","r",stdin);
	freopen("2d.out","w",stdout);

	scanf("%d %d\n", &N, &K);

	assert(1<=K && K<N && N<=200000);

	for (i = 1; i <= N; ++i){
		double aux1, aux2;
		scanf("%lf %lf", &aux1, &aux2);

		assert(-1000000000<=aux1*1000 && aux1*1000<=1000000000);
		assert(-1000000000<=aux2*1000 && aux2*1000<=1000000000);

		A[i] = aux1 * 1000;
	}

	sort(A+1, A+N+1);

	Left = 1000; Right = 2000000000; Sol = 1000;
	while (Left <= Right){
		Mid = (Left + Right) / 2;
		if (Check(Mid)){
			Sol = Mid;
			Right = Mid - 1;
		}
		else
			Left = Mid + 1;
	}

	printf("%d.%d\n", Sol / 1000, Sol % 1000);

	return 0;
}
