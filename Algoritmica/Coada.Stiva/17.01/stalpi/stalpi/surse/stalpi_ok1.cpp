#include<stdio.h>
#include<string.h>

const int lg = 52;

int efort, n, i, dist[lg], d[lg][10005], q[10005];

inline int min(int a, int b){
	return a < b ? a : b;
}
inline int ab(int a){
	return a < 0 ? -a : a;
}

int cost(int val){
	int i, j, end, st;

	memset(d, 0x3f, sizeof(d));

	d[1][0] = 0;

	for (i = 2; i <= n; i ++){
		st = 1, end = 0;
		for (j = 0; j <= val; j ++){
			while (st <= end && d[i - 1][j] <= d[i - 1][ q[end] ])
				end --;

			q[++ end] = j;
		}

		for (j = 0; j <= dist[n]; j ++){
			while (st <= end && j - q[st] > val)
				st ++;

			d[i][j] = d[i - 1][ q[st] ] + ab(j - dist[i]);

			if (j + val + 1 <= dist[n]){
				while (st <= end && d[i - 1][j + val + 1] <= d[i - 1][ q[end] ])
					end --;
				q[++ end] = j + val + 1;
			}
		}

	}

	return d[n][ dist[n] ];
}

int bs(){
	int li = 0, ls = dist[n], x, gs = -1;

	while (li <= ls){
		x = (li + ls) / 2;

		//printf("%d %d\n", x, cost(x));

		if (cost(x) <= efort){
			gs = x;
			ls = x - 1;
		}
		else
			li = x + 1;
	}

	return gs;
}

int main()
{
	freopen("stalpi.in", "rt", stdin);
	freopen("stalpi.out", "wt", stdout);

	scanf("%d%d", &n, &efort);
	for (i = 2; i <= n; i ++)
		scanf("%d", &dist[i]);

	printf("%d\n", bs());

	//cost(17);

	//for (i = 1; i <= n; i ++)
	//	for (int j = 0; j <= dist[n]; j ++)
	//		printf("%d %d  %d\n", i, j, d[i][j]);

	return 0;
}

