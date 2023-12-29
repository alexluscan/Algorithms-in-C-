#include <algorithm>
#include <stdio.h>
#include <vector>

#define MAX 10010
#define pb push_back

using namespace std;

int n, m;
int sel[MAX], parc[MAX], st[MAX], dr[MAX];
vector <int> vctDrum[MAX];
vector <int> vctQ;

bool cupleaza(int nod, int pas)
{
	if (sel[nod] == pas)
		return 0;
	sel[nod] = pas;

	for (int i = 0; i < vctDrum[nod].size(); i++)
		if (!st[vctDrum[nod][i]] || cupleaza(st[vctDrum[nod][i]], pas))
		{
			st[vctDrum[nod][i]] = nod;
			dr[nod] = vctDrum[nod][i];

			return 1;
		}

	return 0;
}

int main()
{
	freopen("felinare.in", "r", stdin);
	freopen("felinare.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int n1, n2;
		scanf("%d %d", &n1, &n2);

		vctDrum[n1].pb(n2);
	}

	for (int ok = 1, pas = 1, i; ok; pas++)
		for (ok = 0, i = 1; i <= n; i++)
			if (!dr[i])
				ok |= cupleaza(i, pas);

	memset(sel, 0, sizeof(sel));
	for (int i = 1; i <= n; i++)
		if (!dr[i])
		{
			sel[i] = 1;

			vctQ.pb(i);
		}

	for (int i = 0; i < vctQ.size(); i++)
		for (int j = 0, nod = vctQ[i]; j < vctDrum[nod].size(); j++)
			if (!parc[vctDrum[nod][j]])
			{
				parc[vctDrum[nod][j]] = 1;
				if (st[vctDrum[nod][j]] && !sel[st[vctDrum[nod][j]]])
					vctQ.pb(st[vctDrum[nod][j]]), sel[st[vctDrum[nod][j]]] = 1;
			}

	int sol = 0;
	for (int i = 1; i <= n; i++)
		sol = sol + (int) (dr[i] > 0);

	printf("%d\n", 2 * n - sol);

	for (int i = 1; i <= n; i++)
		if (sel[i] && parc[i])
			printf("1\n");
		else if (sel[i])
			printf("3\n");
		else if (parc[i])
			printf("0\n");
		else printf("2\n");

	fclose(stdin);
	fclose(stdout);
	return 0;
}
