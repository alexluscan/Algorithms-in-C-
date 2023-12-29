// O(N^5)
#include <fstream>
#include <algorithm>
#include <cmath>
#include <tuple>
using namespace std;

using cost_t = long double;

const int kMaxN = 50;
const cost_t kInf = 1e9;

struct Point {
    int x, y;

    friend cost_t distance(const Point& a, const Point& b) {
        return sqrtl(cost_t(a.x - b.x) * (a.x - b.x) + cost_t(a.y - b.y) * (a.y - b.y));
    }
};

ifstream fin("poligon.in");
ofstream fout("poligon.out");

cost_t cost[kMaxN][kMaxN];
cost_t mn_cost[kMaxN][kMaxN][kMaxN];
pair<int, int> mn_cost_link[kMaxN][kMaxN][kMaxN];
Point p[kMaxN];

void ComputeTransitions(const int left, const int right, const int endpoint) {
    cost_t& ans = mn_cost[left][right][endpoint];
    pair<int, int>& ans_link = mn_cost_link[left][right][endpoint];
    ans = kInf;

    for (int split = left + 1; split <= endpoint; ++split) {
        for (int oth_endpoint = left; oth_endpoint < split; ++oth_endpoint) {
            if (ans > mn_cost[left][split - 1][oth_endpoint] + mn_cost[split][right][endpoint] + cost[endpoint][oth_endpoint]) {
                ans = mn_cost[left][split - 1][oth_endpoint] + mn_cost[split][right][endpoint] + cost[endpoint][oth_endpoint];
                ans_link = make_pair(split, oth_endpoint);
            }
        }
    }

    for (int split = endpoint + 1; split <= right; ++split) {
        for (int oth_endpoint = split; oth_endpoint <= right; ++oth_endpoint) {
            if (ans > mn_cost[left][split - 1][endpoint] + mn_cost[split][right][oth_endpoint] + cost[endpoint][oth_endpoint]) {
                ans = mn_cost[left][split - 1][endpoint] + mn_cost[split][right][oth_endpoint] + cost[endpoint][oth_endpoint];
                ans_link = make_pair(split, oth_endpoint);
            }
        }
    }
}

void BuildSolution(const int left, const int right, const int last_endpoint) {
    if (left == right) {
        return;
    }

    int split, prev_endpoint; tie(split, prev_endpoint) = mn_cost_link[left][right][last_endpoint];
    const int left_endpoint = min(prev_endpoint, last_endpoint);
    const int right_endpoint = prev_endpoint ^ last_endpoint ^ left_endpoint;

    BuildSolution(left, split - 1, left_endpoint);
    BuildSolution(split, right, right_endpoint);

    fout << prev_endpoint + 1 << ' ' << last_endpoint + 1 << '\n';
}

void SolveTest() {
    int n; fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cost[i][j] = cost[j][i] = distance(p[i], p[j]);
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        mn_cost[i][i][i] = 0;
        for (int j = i + 1; j <= n; ++j) {
            for (int k = i; k <= j; ++k) {
                ComputeTransitions(i, j, k);
            }
        }
    }

    int best_endpoint = 0;
    for (int endpoint = 1; endpoint < n; ++endpoint) {
        if (mn_cost[0][n - 1][best_endpoint] > mn_cost[0][n - 1][endpoint]) {
            best_endpoint = endpoint;
        }
    }


    fout << mn_cost[0][n - 1][best_endpoint] << '\n';
    BuildSolution(0, n - 1, best_endpoint);
}

int main() {
    fout.precision(12);
    fout.setf(ios::fixed, ios::floatfield);

    int num_tests; fin >> num_tests;
    while (num_tests--> 0) {
        SolveTest();
    }

    fin.close();
    fout.close();
}
