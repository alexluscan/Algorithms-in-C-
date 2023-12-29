using namespace std;

#include <cstdio>
#include <cassert>

#define FIN "vector.in"
#define FOUT "vector.out"

#define MAX_N 1<<17

int N, A[MAX_N], S, P, X;

void read()
{
	int i;
	FILE *fi = fopen(FIN, "r");
	fscanf(fi, "%d", &N);
	for (i = 1; i < N; ++i)
		fscanf(fi, "%d", A+i);
	fclose(fi);
}

void solve()
{
	int i, tmp;
	for (i = 1; i < N; i += 2)
		S ^= A[i];
	if (S == 0)
		P = X = -1;
	else {
		for (i = 1; i < N; ++i)
			if (i&1) {
				X = A[i]-(S^A[i]);
				if (0 < X && X <= A[i]) {
					P = i;
					break;
				}
			} else {
				X = (S^A[i-1])-A[i-1];
				if (0 < X && X <= A[i]) {
					P = i;
					break;
				}
			}
		A[P] -= X;
		A[P-1] += X;
		for (i = 0; i < N; ++i)
			assert(0 <= A[i] && A[i] < (1<<30));
		for (tmp = 0, i = 1; i < N; i += 2)
			tmp ^= A[i];
		assert(!tmp);
	}
}

void write()
{
	FILE *fo = fopen(FOUT, "w");
	fprintf(fo, "%s\n%d %d\n", S ? "1" : "0", P, X);
	fclose(fo);
}

int main()
{
	read();
	solve();
	write();
	return 0;
}
