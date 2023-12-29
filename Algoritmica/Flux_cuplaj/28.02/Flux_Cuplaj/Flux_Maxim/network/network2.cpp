
	# include <stdio.h>
	# include <string.h>

	# define MN 102

int N, M, C[MN][MN], A[MN][MN];
int S, D, F[MN], U[MN], Q[MN];
int l, r, max_flow, sol;

void read_data()
{
	int i, x, y;
	FILE *f = fopen("network.in", "rt");
	fscanf(f, "%d %d", &N, &M);
	for (i=0; i<M; i++)
	{
		fscanf(f, "%d %d", &x, &y);
		C[x][y] = C[y][x] = 1;
	}
	fclose(f);
}

int BFS()
{
	memset( F, 0, sizeof(F) );
	register int i, k;
	Q[l=r=0]=S, F[S] = 1;
	for (; l<=r && !F[D]; l++)
	for (k=Q[l], i=2; i<=N; i++)
	if (!F[i] && A[k][i])
		F[i] = 1, U[i] = k, Q[++r] = i;
	if (!F[D]) return 0;
	max_flow++;
	for (i=D; i>1; i=U[i])
		A[U[i]][i] --, A[i][U[i]]++;
	return 1;
}

void process()
{
	for (S=1, sol=N-1, D=2; D<=N; D++)
	{
		memcpy( A, C, sizeof(C) );
		for (max_flow = 0; BFS(); );
		if (sol > max_flow) sol = max_flow;
	}
}

void write_data()
{
	FILE *f = fopen("network.out", "wt");
	fprintf(f, "%d\n", sol);
	fclose(f);
}

int main()
{
	read_data();
	process();
	write_data();
	return 0;
}
