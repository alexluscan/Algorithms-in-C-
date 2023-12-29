#include <fstream>
#include <vector>
 
using namespace std;
 
const int MAXN = 20;
const int MAXX = 262150;
const int INF = 100000000;
 
int N, M, Sol;
int Cost[MAXN][MAXN];
int C[MAXX][MAXN];
vector <int> A[MAXN];
 
int main()
{
    ifstream fin("hamilton.in");
    ofstream fout("hamilton.out");
 
    fin >> N >> M;
 
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) Cost[i][j] = INF;
 
    for (int i = 1; i <= M; ++i)
    {
        int x, y;
 
        fin >> x >> y;
        A[y].push_back(x);
        fin >> Cost[x][y];
    }
 
    for (int i = 0; i < 1 << N; ++i)
        for (int j = 0; j < N; ++j) C[i][j] = INF;
 
    C[1][0] = 0;
 
    for (int i = 0; i < 1 << N; ++i)
        for (int j = 0; j < N; ++j)  // j si k sunt in submultimea i
            if (i & (1 << j))
                for (const int& k : A[j]) // dintre toate arcele k -> j care indica spre j 
                    if (i & (1 << k))     // aleg un k din submultime 
                        C[i][j] = min(C[i][j], C[i ^ (1 << j)][k] + Cost[k][j]); 
 
    Sol = INF;
    // consider 0 nodul de plecare
    for (const int& i : A[0]) // pt toate lanturile care se termina cu un i
        Sol = min(Sol, C[(1<<N) - 1][i] + Cost[i][0]);   // daca am arc de la i la 0
 
    if (Sol == INF) fout << "Nu exista solutie\n";
    else fout << Sol << '\n';;
 
    return 0;
}
