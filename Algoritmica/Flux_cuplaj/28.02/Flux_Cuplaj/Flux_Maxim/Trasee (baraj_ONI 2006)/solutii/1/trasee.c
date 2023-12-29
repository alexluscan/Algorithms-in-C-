#include <stdio.h>
#include <stdlib.h>
#define filein "trasee.in"
#define fileout "trasee.out"
#define NMax 256
typedef struct lista {
						int id;
						struct lista *next;
					 } lista;
typedef lista *Graf[NMax + 1];
typedef int queue[NMax + 1];
typedef int matrix[NMax + 1][NMax + 1];

int n, x, k;
Graf G;

int grad[NMax + 1], D; // D = destinatia retelei de transport
queue q, d, ant;
Graf T;

matrix c, f; // matricile de capacitate si flux

int Best = 0;

void add_to_list(lista **l, int item)
{
	lista *tmp = (lista *)malloc(sizeof(lista));

	tmp->id = item;
	tmp->next = *l;
	*l = tmp;
}

void citire()
{
	FILE *fin = fopen(filein, "r");
	int i, a, b, m;

		fscanf(fin, "%d %d %d %d", &n, &m, &x, &k);

		for (i = 1; i <= n; i++) G[i] = NULL;

		for (i = 1; i <= m; i++)
		{
			fscanf(fin, "%d %d", &a, &b);
			add_to_list(&G[a], b);
			add_to_list(&G[b], a);
		}

	fclose(fin);
}

void compute()
{
	int i, j, cur, fin;
	lista *g;

	for (i = 1; i <= n; i++) d[i] = 0;

	cur = 1; fin = 1; q[1] = x; d[x] = 1;
	while (cur <= fin)
	{
		for (g = G[q[cur]]; g; g = g->next)
			if (d[g->id] == 0)
			{ fin++; q[fin] = g->id; d[q[fin]] = d[q[cur]] + 1; }

		cur++;
	}

	for (i = 1; i <= n; i++) T[i] = NULL;

	for (i = 1; i <= n; i++)
	{
		grad[i] = 0;
		for (j = 1; j <= n; j++)
			c[i][j] = f[i][j] = 0;
	}

	for (i = 1; i <= n; i++)
		for (g = G[i]; g; g = g->next)
			if (d[g->id]+1 == d[i] && d[i] <= k)
			// g->id poate fi predecesorul lui i pe un drum
			{
				add_to_list(&T[g->id], i);
				add_to_list(&T[i], g->id);
				grad[i]++;
				c[g->id][i] = 1;
			}

	D = n+1;
	for (i = 1; i <= n; i++)
		if (d[i] == k)
		{
			add_to_list(&T[i], D);
			add_to_list(&T[D], i);
			c[i][D] = grad[i];
		}
}

int augment()
{
	lista *g;
	int cur, fin, i;

	for (i = 1; i <= n+1; i++) q[i] = d[i] = ant[i] = 0;

	cur = fin = 1; q[1] = x; d[x] = 1; ant[1] = 0;
	while (cur <= fin)
	{
		for (g = T[q[cur]]; g; g = g->next)
			if (c[q[cur]][g->id] - f[q[cur]][g->id] > 0 && !d[g->id])
			{ fin++; q[fin] = g->id; d[g->id] = 1; ant[fin] = cur;
			  if (q[fin] == D) break;
			}
		if (q[fin] == D) break;

		cur++;
	}

	if (q[fin] != D) return 0;

	for (cur = fin; ant[cur] > 0; cur = ant[cur])
	{
		f[q[ant[cur]]][q[cur]]++;
		f[q[cur]][q[ant[cur]]] = -f[q[ant[cur]]][q[cur]];
	}

	Best++; // s-a marit fluxul cu o unitate
	return 1;
}

void print()
{
	FILE *fout = fopen(fileout, "w");

		fprintf(fout, "%d\n", Best);

	fclose(fout);
}

int main()
{
	citire();
	compute();
    while (augment());
	print();
	return 0;
}
