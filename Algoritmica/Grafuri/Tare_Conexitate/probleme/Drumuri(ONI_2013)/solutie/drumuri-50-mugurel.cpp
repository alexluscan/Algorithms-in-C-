// Mugurel Ionut Andreica
// Brute force: O(N * (N + M))

#include <stdio.h>
#include <vector>

using namespace std;

#define NMAX 150111

vector<int> vec[NMAX][2];
int N, M;

void ReadInput() {
	int i, j, k;
	freopen("drumuri.in", "r", stdin);
	scanf("%d %d", &N, &M);
	for (k = 1; k <= M; k++) {
		scanf("%d %d", &i, &j);
		vec[i][0].push_back(j);
		vec[j][1].push_back(i);
	}
}

int visited[NMAX][2];
int qnode[2 * NMAX], qdir[2 * NMAX], li, ls;

int IsPopular(int start) {
	int i, dir, j, k, nviz = 1;

	qnode[1] = start; qdir[1] = 0;
	qnode[2] = start; qdir[2] = 1;
	li = 1; ls = 2;
	visited[start][0] = visited[start][1] = start;
	
	while (li <= ls && nviz < N) {
		i = qnode[li];
		dir = qdir[li];
		li++;

		for (k = 0; k < vec[i][dir].size(); k++) {
			j = vec[i][dir][k];
			if (visited[j][dir] != start) {
				visited[j][dir] = start;
				ls++;
				qnode[ls] = j;
				qdir[ls] = dir;
				if (visited[j][1 - dir] != start)
					nviz++;
			}
		}
	}

	//fprintf(stderr, "start=%d nviz=%d ls=%d\n", start, nviz, ls);
	return (nviz == N);
}

char popular[NMAX];

void Solve() {
	M = 0;
	for (int start = 1; start <= N; start++) {
		if (IsPopular(start)) {
			popular[start] = 1;
			M++;
		} else
			popular[start] = 0;
	}
}

void WriteOutput() {
	int i;
	freopen("drumuri.out", "w", stdout);
	printf("%d\n", M);
	for (i = 1; i <= N; i++)
		if (popular[i])
			printf("%d ", i);
	printf("\n");
}

int main() {
	ReadInput();
	Solve();
	WriteOutput();
	return 0;
}
