#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>

using namespace std;

const int MAXN = 64;
const int MAXD = 1 << 14;

int N, E;
int D[MAXN];
int bst[MAXN][MAXD];
deque<int> st;

inline int isOk(int dist) {
    memset(bst, 0x3f, sizeof(bst));
    bst[0][0] = 0;
    for (int i = 1; i < N - 1; i++) {
        st.clear();
        for (int j = 0; j <= D[N - 1]; j++) {
            for (; !st.empty() && bst[i - 1][j] <= bst[i - 1][st.back()]; st.pop_back());
            st.push_back(j);
            if (j - st.front() > dist) {
                st.pop_front();
            }
            bst[i][j] = bst[i - 1][st.front()] + abs(j - D[i]);
        }
    }

    int MIN = 0x3f3f3f3f;
    for (int j = max(0, D[N - 1] - dist); j <= D[N - 1]; j++) {
        MIN = min(MIN, bst[N - 2][j]);
    }
    return MIN <= E;
}

int main() {
    freopen("stalpi.in", "rt", stdin);
    freopen("stalpi.out", "wt", stdout);

    scanf("%d %d", &N, &E);

    for (int i = 1; i < N; i++) {
        scanf("%d", D + i);
    }

    int rez = -1, step = MAXD;
    for (; step; step >>= 1) {
        if (!isOk(rez + step)) {
            rez += step;
        }
    }
    printf("%d\n", rez + 1);

    return 0;
}
