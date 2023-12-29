#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using VI = vector<int>;
using VB = vector<bool>;
const int Inf = 0x3f3f3f3f;

int n, m, source, dest, maxFlow;
vector<VI> cap, flow;
VB v;
VI t, Min;

void Read();
void EdmondsKarp();
void Write();
void BuildGraph();
bool BfPath(int nod);

int main()
{
    Read();
    EdmondsKarp();
    Write();
    
    return 0;
}

void Read()
{
    FILE *fin = fopen("T17.IN", "r");
    fscanf(fin, "%d%d%d%d", &n, &m, &source, &dest);
    BuildGraph();
    for (int i = 1, x, y; i <= m; ++i)
    {
        fscanf(fin, "%d%d", &x, &y);
        cap[2*x + 1][2*y] = 1;
        cap[2*y + 1][2*x] = 1;
    }
    fclose(fin);
}

void BuildGraph()
{
    cap = flow = vector<VI>(2*n + 6);
   
    Min = VI(2 * n + 6);
    for (int i = 0; i <= 2*n + 4; ++i)
    {
        cap[i].resize(2*n + 6);
        flow[i].resize(2*n + 6);
    }

    for (int i = 1; i <= n; ++i)
    {
        cap[2*i][2*i + 1] = 1;
        cap[2*i + 1][2*i] = 1;
    }
    cap[2*source][2*source+1] = Inf;
    cap[2*source + 1][2*source] = Inf;
    cap[2*dest][2*dest + 1] = Inf;
    cap[2*dest + 1][2*dest] = Inf;
    source = 2*source;
    dest = 2*dest + 1;
}

void EdmondsKarp()
{
    int tata;
    while (BfPath(source)) // cat timp avem drum
    { 
		// pompeaza
        maxFlow += Min[dest]; // updatam flux
                 
        for (int x = dest; x != source; x = tata)
        {
            tata = t[x];
			flow[tata][x] += Min[dest];
			flow[x][tata] -= Min[dest];

        }
    }
}

bool BfPath(int x) 
{
    v = VB(2 * n + 4);
    t = VI(2 * n + 4);
    Min.assign(2 * n + 4, Inf);
     
    queue<int> Q;
    Q.push(x);  v[x] = true;
    while (!Q.empty())
    {
        x = Q.front(); Q.pop();
        for (int y = 0; y <= 2 * n + 4; ++y)
        {    
			if (v[y]) continue;
			if (cap[x][y] > flow[x][y]) // daca mai putem pompa
			{
				Min[y] = min(cap[x][y] - flow[x][y], Min[x]);
				v[y] = true; t[y] = x;
				Q.push(y);
			}                
        }
    }
    return v[dest];
}

void Write()
{
    FILE *fout = fopen("joc.out", "w");
    fprintf(fout, "%d\n", maxFlow);
    fclose(fout);
}
 
