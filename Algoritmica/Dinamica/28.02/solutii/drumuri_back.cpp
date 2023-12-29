#include <fstream>
#define MOD 31607
#define DIM 1010

using namespace std;

int a[DIM][DIM];

int n, m, k, L, i, j, sol, x, y;

void back(int i, int j, int p) {
    if (a[i][j] == 1) {
        k--;
    }
    if (p == L) {
        if (k == 0) {
            sol++;
            if (sol == MOD)
                sol = 0;
        }
        if (a[i][j] == 1) {
            k++;
        }
        return;
    }
    if (i!=n)
        back(i+1, j, p+1);
    if (j!=n)
        back(i, j+1, p+1);
    if (a[i][j] == 1) {
        k++;
    }
}


int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");
    fin>>n>>m>>k>>L;
    for (i=1;i<=m;i++) {
        fin>>x>>y;
        a[x][y] = 1;
    }

    back(1, 1, 1);
    fout<<sol<<"\n";
    return 0;
}
