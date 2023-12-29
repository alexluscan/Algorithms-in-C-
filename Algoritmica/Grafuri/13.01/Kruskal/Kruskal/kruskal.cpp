// Det Arb Partial de Cost Minim ( Minimum Spanning Tree)
// Arb minim de acoperire
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

ifstream fin("kruskal.in");
ofstream fout("graf.out");

const int Dim = 10000;
int t[Dim];
int h[Dim];

struct Edge {
    Edge(int a = 0, int b = 0, int c = 0)
       : x(a), y(b), cost(c)
    {
    }
    int x, y, cost;
};


vector<Edge> G, apm;
int cmin, n;

bool Cmp(const Edge& e1, const Edge& e2)
{
    return e1.cost < e2.cost;
}


void Read();
void Write();
void Kruskal();

void Union(int r1, int r2);  // unifica multimea care il cont pe r1 ca radacina cu mult care il cont pe r2 ca rad
int Find(int x);  // returneaza multimea careia ii apartine x

int main()
{
    Read();
    for ( int i = 1; i <= n; ++i )
        t[i] = i;
    Kruskal();
    Write();
    fout.close();
}

void Kruskal()
{
    sort(G.begin(), G.end(), Cmp);    // O(m * log m)

    int cnt = 0, r1, r2;
    for ( const auto& m : G ) // O(n)
    {
        r1 = Find(m.x), r2 = Find(m.y); // O(1) amortizat

        if ( r1 == r2 ) continue; // daca fac parte din aceeasi multime
        apm.push_back(m);
        cmin += m.cost;
        cnt++;
        if ( cnt == n - 1 )
            break;
    }
}

void Write()
{
    fout << "Costul minim: " << cmin << '\n';
    for ( vector<Edge>::iterator it = apm.begin(); it != apm.end(); ++it )
        fout << it->x << ' ' << it->y << ' ' << it->cost << '\n';
}

void Read()
{
    fin >> n;
    int x, y, cost;
    while ( fin >> x >> y >> cost )
        G.push_back(Edge(x, y, cost));
    fin.close();
}

int Find(int x)
{
    if ( x == t[x] )
        return x;
    return t[x] = Find(t[x]);
}
/*
int Find(int x)
{
    int r, y = x;
    while ( y != t[y] )
        y = t[y];
    r = y;

    while ( x != r ) // compresie
    {
        y = t[x];
        t[x] = r;
        x = y;
    }
}
*/
void Union(int r1, int r2)
{
    if ( h[r1] > h[r2] )
        t[r2] = r1;
    else
    {
        t[r1] = r2;
        if ( h[r1] == h[r2] )
            h[r2]++;
    }
}



