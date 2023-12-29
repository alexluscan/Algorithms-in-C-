/*  OK 
 *  Pictures - perimetrul figurii
	baleiere + arbori de intervale
 	Complexitate: O(N * lg MAXC) }
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

struct Edge {
    int x, y1, y2, sgn;
    bool operator < (const Edge& e) const
    {
		return x < e.x || ( x == e.x && sgn < e.sgn );
	}
};

vector<Edge> V, H;   // 5000 dreptunghiuri a cate 4 segmente = 20000 segmente
int N, Cnt[4 * 20000], Sum[4 * 20000];

#define mid  ( (l + r) / 2 - ((l + r) % 2 && (l + r < 0)) )

void Update(int n, int l, int r, int a, int b, int c)  
{
   if (a <= l && r <= b)
      Cnt[n] += c;
   else
   {
		if (a <= mid)
			Update(2 * n, l, mid, a, b, c);
		if (b > mid)
			Update(2 * n + 1, mid + 1, r, a, b, c);
    }
    // portiunea acoperita pe oy
    Sum[n] = 0;
    if ( Cnt[n] )
		Sum[n] = (r - l + 1);
	else
		if ( l < r )
			Sum[n] = Sum[2 * n] + Sum[2 * n + 1];
}

int solve(vector<Edge> E)
{
    int i, t = 0, P = 0;
	// Ordinea de sortare: segment stanga, segment dreapta
    sort(E.begin(), E.end());       // 2 * N elemente
    memset(Cnt, 0, sizeof(Cnt));
    memset(Sum, 0, sizeof(Sum));

    for (i = 0; i < 2 * N; i++) 
        Update(1, -10001, 10001, E[i].y1, E[i].y2 - 1, E[i].sgn),
        P += abs(Sum[1] - t), t = Sum[1];   // se adauga numai variatia lungimii acoperite pe OY
    return P;
}

int main()
{
    FILE *f;
    int x1, y1, x2, y2;

    f = fopen("picture3.in", "r");
    //fscanf(f, "%d\n", &N);
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++)
    {
	//	fscanf(f, "%d %d %d %d",&x1, &y1, &x2, &y2);
		scanf("%d %d %d %d",&x1, &y1, &x2, &y2);
	
		V.push_back({x1, y1, y2, -1}); // segmentul din stanga dreptunghiului // semnul identifica segmentul (stanga sau dreapta)
        V.push_back({x2, y1, y2, +1});

		H.push_back({y1, x1, x2, -1}); //schimba axa OX cu OY // segm oriz devin verticale
        H.push_back({y2, x1, x2, +1});
    }
    fclose(f);

    f = fopen("drept.out", "w");
    // fprintf(f, "%d\n", solve(V) + solve(H));
    printf("%d\n", solve(V) + solve(H));
    fclose(f);

    return 0;
}
