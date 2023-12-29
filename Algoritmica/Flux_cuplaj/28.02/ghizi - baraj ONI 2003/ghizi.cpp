#include <stdio.h>

int N, K, C[101][101], G[5001][2];
int queue[101], up[101], sol[5001], count;

int augument()
{
    int i, j, head, tail;

    for (i = 0; i < 101; i++)
        queue[i] = 0, up[i] = -1;

    queue[0] = 0; up[0] = 0;
    for (head = tail = 0; head <= tail; head++)
    {
        i = queue[head];
        for (j = 0; j < 101; j++)
            if (C[i][j] && up[j] == -1)
            {
                up[j] = i;
                queue[++tail] = j;
                if (j == 100) return 1;
            }
    }
    return 0;
}

int main()
{
    FILE *f;
    int i, j, k;

    f = fopen("ghizi.in", "r");
    fscanf(f, "%d %d\n", &N, &K);
    for (k = 1; k <= N; k++)
    {
        fscanf(f, "%d %d\n", &i, &j);   // timpii t1 si t2 pt fiecare ghid k
        C[i][j]++;                  // capacitatea retelei intre nodurile (i, j)
        G[k][0] = i, G[k][1] = j; // primul si al doilea varf al muchiei k
    }
    fclose(f);

    while (K)
    {
        if (!augument()) 
			break; 
		K--;
        for (i = 100; i; i = up[i])
            C[up[i]][i]--,
            C[i][up[i]]++;
    }

    f = fopen("ghizi.out", "w");
    for (i = 1; i <= N; i++)
		if (C[G[i][1]][G[i][0]] >= 1)
		   sol[count++] = i,
		   C[G[i][1]][G[i][0]]--;
       
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; i++)
        fprintf(f, "%d ", sol[i]);
    fprintf(f, "\n");
    fclose(f);

    return 0;
}

