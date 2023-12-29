#include <stdio.h>
#include <string.h>

int N, M, D, Q[105], Up[105], Res = 10666;
char C[105][105], F[105][105];

int augument(void)
{
	int i, j, ql, qr;

	Q[0] = 0;
	for (i = 0; i < N; Up[i++] = -1);
	for (ql = qr = 0; ql <= qr; ql++)
	for (i = Q[ql], j = 0; j < N; j++)
	if (Up[j] == -1 && C[i][j] > F[i][j])
	{
		Up[Q[++qr] = j] = i;
		if (j == D) return 1;
	}
	return 0;
}

int max_flow(void)
{
	int i, flow;

	for (flow = 0; augument(); flow++)
	for (i = D; i > 0; i = Up[i])
		F[Up[i]][i]++, F[i][Up[i]]--;
	return flow;
}

int main(void)
{
	FILE *f;
	int i, j;

	f = fopen("network.in", "r");
	fscanf(f, "%d %d\n", &N, &M);
	for (; M; M--)
		fscanf(f, "%d %d\n", &i, &j), i--, j--,
		C[i][j] = C[j][i] = 1;
	fclose(f);

	for (i = 1; i < N; i++)
	{
		memset(F, 0, sizeof(F));
		D = i, j = max_flow();
		if (Res > j) Res = j;
	}

	f = fopen("network.out", "w");
	fprintf(f, "%d\n", Res);
	fclose(f);

	return 0;
}