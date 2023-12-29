#include <algorithm>
#include <stdio.h>

#define MAX 128

using namespace std;

int n, m;
char matAd[MAX][MAX];
int dr[MAX], st[MAX], sel[MAX];

bool cupleaza(int nod, int pas)
{
	if (sel[nod] == pas)
		return 0;
	sel[nod] = pas;

	for (int i = 1; i <= m; i++)
		if (matAd[nod][i] == '1' && (!st[i] || cupleaza(st[i], pas)))
		{
			st[i] = nod;
			dr[nod] = i;

			return 1;
		}

	return 0;
}

int main()
{
	freopen("paznici.in", "r", stdin);
	freopen("paznici.out", "w", stdout);
	
	scanf("%d %d\n", &n, &m);

	for (int i = 1; i <= n; i++)
		fgets(matAd[i] + 1, MAX, stdin);

	for (int ok = 1, pas = 1, i; ok; pas++)
		for (ok = 0, i = 1; i <= n; i++)
			if (!dr[i])
				ok |= cupleaza(i, pas);

	memset(sel, 0, sizeof(sel));
	for (int ok = 1; ok; )
	{
		ok = 0;
		for (int i = n; i; i--)
			if (dr[i])
				for (int j = 1; j <= n; j++)
					if (matAd[j][dr[i]] == '1' && !dr[j])
					{
						ok = 1;
						sel[dr[i]] = 1;
						dr[i] = 0;

						break;
					}
	}

	for (int i = 1; i <= n; i++)
		if (dr[i])
			printf("%c", 'A' - 1 + i);
	for (int i = 1; i <= m; i++)
		if (sel[i])
			printf("%c", 'a' - 1 + i);
	printf("\n");

	fclose(stdin);
	fclose(stdout);
	return 0;
}
