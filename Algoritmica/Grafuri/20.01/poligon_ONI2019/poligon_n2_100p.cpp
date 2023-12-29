// Andrei Constantinescu - Oxford University
// O(N^2)
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;
const int NMAX = 2000 + 5;

int N;
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}

    friend inline long double dist(const Point &A, const Point &B) {
        return sqrtl(1LL * (A.x - B.x) * (A.x - B.x) +
                    1LL * (A.y - B.y) * (A.y - B.y));
    }
} points[NMAX];

const long double INF = 1E9L;

long double costMin[NMAX];
bool vis[NMAX];
int father[NMAX];

vector <int> mst[NMAX];

ifstream fin("poligon.in");
ofstream fout("poligon.out");

void read() {
    for (int i = 1; i <= N; ++ i)
        father[i] = 0, mst[i].clear();

    fin >> N;
    for (int i = 1; i <= N; ++ i) 
        fin >> points[i].x >> points[i].y;
}

long double solvePrim() {
    for (int i = 1; i <= N; ++ i)
        costMin[i] = INF, vis[i] = false;
    costMin[1] = 0;

    // Prim's Algo
    long double cost = 0;
    for (int phase = 1; phase <= N; ++ phase) {
        int node = -1;
        long double dMin = INF + 5;
        for (int i = 1; i <= N; ++ i)
            if (!vis[i] && costMin[i] < dMin)
                node = i, dMin = costMin[i];

        vis[node] = true;
        cost += costMin[node];
        mst[node].push_back(father[node]);
        mst[father[node]].push_back(node);

        for (int i = 1; i <= N; ++ i)
            if (!vis[i]) {
                const long double dst = dist(points[node], points[i]);
                if (dst < costMin[i]) {
                    costMin[i] = dst;
                    father[i] = node;
                }
            }
    }

    return cost;
}

int nxt[NMAX], prc[NMAX], deg[NMAX];

vector <pair <int, int> > printSolution() {
    for (int i = 1; i < N; ++ i)
        nxt[i] = i + 1, prc[i + 1] = i;
    nxt[N] = 1, prc[1] = N;

    for (int i = 1; i <= N; ++ i)
        deg[i] = mst[i].size(), vis[i] = false;

    vector <pair <int, int> > ans;

    for (int phase = 1; phase < N; ++ phase) {
        for (int i = 1; i <= N; ++ i)
            if (!vis[i] && deg[i] == 1) {
                int node;
                for (auto it: mst[i])
                    if (!vis[it]) {
                        node = it;
                        break;
                    }
                if (node == nxt[i] || node == prc[i]) {
                    ans.push_back({i, node});
                    vis[i] = true;
                    -- deg[node];
                    nxt[prc[i]] = nxt[i], prc[nxt[i]] = prc[i];
                }
            }
    }
    return ans;
}

void test() {
    read();
    fout << fixed << setprecision(12);
    fout << solvePrim() << '\n';
    vector <pair <int, int> > sol = printSolution();
    for (auto it: sol)
        fout << it.first << ' ' << it.second << '\n';
}

int main() {
    int T = 0;
    fin >> T;
    while (T --)
        test();
    return 0;
}
