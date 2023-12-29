/* 100 puncte
    prof. Eugen Nodea
*/
# include <cstdio>
using namespace std;

struct cladire
{
    short x1, y1, x2, y2;
    int l, L;
}C[1002];
short n, m, k;
bool A[1502][1502];
short l[1502], c[1502];

int main()
{
    int i, j, p, Max, a, nr;
    freopen("harta.in", "r", stdin);
    freopen("harta.out","w", stdout);
    scanf("%d", &p);
    scanf("%hd %hd %hd", &n, &m, &k);
    for (i=1; i<=k; ++i)
        scanf("%hd %hd %hd %hd", &C[i].x1, &C[i].y1, &C[i].x2, &C[i].y2);
    if (p == 1)
    {
        Max = 0;
        for (i=1; i<=k; ++i)
        {
            C[i].l = C[i].x2 - C[i].x1 + 1;
            C[i].L = C[i].y2 - C[i].y1 + 1;
            if (C[i].l == C[i].L)
            {
                if (C[i].l > Max) Max = C[i].l;
            }
        }
        a = (Max - 1) * (Max - 1);
        nr = 0;
        for (i=1; i<=k; ++i)
            if (C[i].l * C[i].L <= a && C[i].l < Max - 1 && C[i].L < Max - 1) ++nr;
        printf("%d %d\n", Max * Max, nr);
    }
    else
    {
        for (; k>0; --k)
        {
            for (i=C[k].x1; i<=C[k].x2; ++i)
            {
                A[i][C[k].y1] = A[i][C[k].y2] = 1;
                l[i] = 1;
            }
            for (i=C[k].y1; i<=C[k].y2; ++i)
            {
                A[C[k].x1][i] = A[C[k].x2][i] = 1;
                c[i] = 1;
            }
        }
        for (i=1; i<=m; ++i)
            if (c[i] == 0)
            {
                j = i + 1;
                while (c[j] == 0 && j <= m)
                    c[j++] = 2;
            }
        for (i=1; i<=n; ++i)
            if (l[i] == 0)
            {
                j = i + 1;
                while (l[j] == 0 && j <= n)
                    l[j++] = 2;
            }
        for (i=1; i<=n; ++i)
        {
            if (l[i] < 2)
            {
                for (j=1; j<=m; ++j)
                    if (c[j] < 2) printf("%d ", (int) A[i][j]);
                printf("\n");
            }
        }
    }
    return 0;
}
