// Mugurel Ionut Andreica
// Time Complexity: O(lungime sir * numar cuvinte)
// nu depinde de lungime maxima a unui cuvant

#include <stdio.h>
#include <string.h>

#define LMAX 210
#define NMAX 210
#define LCUV 20
#define SIGMA 256
#define PMOD 1000003
#define INF 65000

char sir[LMAX], spaceAfter[LMAX], vocale[SIGMA];
long int nrpos[LMAX][2], sprefix[LMAX];
long int cmin[LMAX][2];
unsigned char prev[LMAX][NMAX];
long int i, j, k, N, M, lastVoc, prevLastVoc, sum, li, ls;
long int ydq[LMAX], wdq[LMAX], pozdq[LMAX], pozfirst[LMAX];
long int y, w, pozf, ykdq, dy, dx, xcross;

void nr_posib()
{
	nrpos[0][0] = 1;
	for (i = 1; i <= M; i++)
		nrpos[i][0] = 0;

	for (j = 1; j <= N; j++)
	{
		sprefix[0] = nrpos[0][(j - 1) % 2];
		for (i = 1; i <= M; i++)
			sprefix[i] = (sprefix[i - 1] + nrpos[i][(j - 1) % 2]) % PMOD;

		lastVoc = -LCUV - 1;

		nrpos[0][j % 2] = 0;
		for (i = 1; i <= M; i++)
		{
			if (vocale[sir[i]])
				lastVoc = i;

			if (lastVoc >= i - LCUV + 1)
			{
				if (i - LCUV - 1>= 0)
					nrpos[i][j % 2] = (sprefix[lastVoc - 1] - sprefix[i - LCUV - 1] + PMOD) % PMOD;
				else
					nrpos[i][j % 2] = sprefix[lastVoc - 1];
			}
		}
	}

	printf("%ld\n", nrpos[M][N % 2]);
}

void armonie_optima()
{
	// initializare
	cmin[0][0] = 0;
	for (i = 1; i <= M; i++)
		cmin[i][0] = INF;

	// programare dinamica
	for (j = 1; j <= N; j++)
	{
		li = 1;
		ls = 0;

		lastVoc = -LCUV - 1;

		cmin[0][j % 2] = INF;

		for (i = 1; i <= M; i++)
		{
			if (vocale[sir[i]])
			{
				prevLastVoc = lastVoc;
				lastVoc = i;

				if (prevLastVoc < 0)
					prevLastVoc = 0;

				for (k = prevLastVoc; k < lastVoc; k++)
					if (k >= i - LCUV && cmin[k][(j - 1) % 2] < INF)
					{
						// insert into the deque
						y = cmin[k][(j - 1) % 2] - k * k;
						w = -2*k;
						pozf = k;

						while (ls >= li)
						{
							ykdq = ydq[ls] + wdq[ls] * (k - pozdq[ls]);
							if (y < ykdq)
								ls--;
							else
							{
								dy = y - ykdq;
								dx = dy / (wdq[ls] - w);

								if (y + dx * w >= ykdq + dx * wdq[ls])
									dx++;

								xcross = k + dx;

								if (xcross <= pozfirst[ls])
									ls--;
								else
								{
									pozf = xcross;
									break;
								}
							}
						}

						ls++;
						ydq[ls] = y;
						wdq[ls] = w;
						pozdq[ls] = k;
						pozfirst[ls] = pozf;
					}
			}
			
			if (lastVoc >= i - LCUV + 1)
			{
				// clean up the front of the deque
				while (li <= ls && pozdq[li] < i - LCUV)
					li++;

				while (li < ls && pozfirst[li + 1] <= i)
					li++;

				if (li > ls)
				{
					cmin[i][j % 2] = INF;
					prev[i][j] = 0;
				}
				else
				{
					cmin[i][j % 2] = i * i + ydq[li] + wdq[li] * (i - pozdq[li]);
					prev[i][j] = pozdq[li];
				}
			}
			else
				cmin[i][j % 2] = INF;
		}
	}

	printf("%ld\n", cmin[M][N % 2]);

	// reconstituire
	i = M; j = N;

	memset(spaceAfter, 0, sizeof(spaceAfter));

	while (i >= 1 && j >= 1)
	{
		spaceAfter[prev[i][j]] = 1;
		i = prev[i][j];
		j--;
	}

	for (i = 1; i <= M; i++)
	{
		printf("%c", sir[i]);
		if (spaceAfter[i])
			printf(" ");
	}

	printf("\n");
}

int main()
{
	memset(vocale, 0, sizeof(vocale));
	vocale['a'] = 1;
	vocale['e'] = 1;
	vocale['i'] = 1;
	vocale['o'] = 1;
	vocale['u'] = 1;
	vocale['y'] = 1;

	freopen("text.in", "r", stdin);
	scanf("%s %ld", sir + 1, &N);
	M = strlen(sir + 1);

	freopen("text.out", "w", stdout);
	nr_posib();
	armonie_optima();

	return 0;
}
