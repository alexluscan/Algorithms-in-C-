#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& cout, const vector<int> &V) {
    cout << V.size() << "\n";

    for (vector<int>::const_iterator it = V.begin(); it != V.end(); ++it)
        cout << *it + 1 << " ";
    cout << "\n";
    return cout;
}


class Graph {
  public:
    Graph(const int &size):
        edges_(size) {
    }

    void addArc(const int &from, const int &to) {
        edges_[from].push_back(to);
    }

    vector<int> kernels() {
        lowlink = index = scc = vector<int>(edges_.size(), 0);
        indecs = 0;

        for (int i = 0; i < int(edges_.size()); ++i) {
            tarjan(i);
        }

        vector<int> bestLeft(sccs.size(), 1), bestRight(sccs.size(), 1), aux(sccs.size(), 1);
        for (int i = 0; i < int(sccs.size()); ++i) {
            for (vector<int>::iterator it = sccs[i].begin(); it != sccs[i].end(); ++it) 
                for (vector<int>::iterator jt = edges_[*it].begin(); jt != edges_[*it].end(); ++jt)
                    if (i != scc[*jt]) {
                        aux[i] += aux[scc[*jt]];
                        aux[scc[*jt]] = 0;
                    }
            bestLeft[i] = aux[i];
        }

        vector<bool> ok(edges_.size(), false);
        int total = 0;
        for (int i = sccs.size() - 1; i >= 0; --i) {
            if (bestLeft[i] + bestRight[i] == int(sccs.size()) + 1) {
                total += sccs[i].size();
                for (vector<int>::iterator it = sccs[i].begin(); it != sccs[i].end(); ++it)
                    ok[*it] = true;
            }

            int minplace = -1;
            for (vector<int>::iterator it = sccs[i].begin(); it != sccs[i].end(); ++it)
                for (vector<int>::iterator jt = edges_[*it].begin(); jt != edges_[*it].end(); ++jt)
                    if (i > scc[*jt] && scc[*jt] > minplace)
                        minplace = scc[*jt];

            if (minplace != -1)
                bestRight[minplace] += bestRight[i];
        }

        vector<int> answer;
        answer.reserve(total);
        for (int i = 0; i < int(edges_.size()); ++i)
            if (ok[i])
                answer.push_back(i);
        return answer;
   }

  private:
    void tarjan(const int &node) {
        if (lowlink[node] != 0)
            return;

        index[node] = lowlink[node] = ++indecs;
        S.push(node);

        for (vector<int>::iterator it = edges_[node].begin(); it != edges_[node].end(); ++it)
            if (index[*it] == 0) {
                tarjan(*it);
                lowlink[node] = min(lowlink[node], lowlink[*it]);
            } else
                if (index[*it] != -1) {
                    lowlink[node] = min(lowlink[node], lowlink[*it]);
                }
       
        //cerr << node + 1 << " -> " << lowlink[node] << " " << index[node] << "\n";
        if (lowlink[node] == index[node]) {
            vector<int> now;
            int nod;
            do {
                nod = S.top();
                S.pop();
                now.push_back(nod);
                scc[nod] = sccs.size();
                index[nod] = -1;
            } while (nod != node);

            sccs.push_back(now);
        }

    }

    void randomSort() {
        for (int i = 0; i < int(sccs.size()); ++i)
            random_shuffle(E[i].begin(), E[i].end());
 
        vector<int> list(sccs.size());
        for (int i = 0; i < int(sccs.size()); ++i)
            list[i] = i;
        random_shuffle(list.begin(), list.end());

        top.clear();
        been = vector<bool>(sccs.size(), false);
        for (int i = 0; i < int(sccs.size()); ++i)
            dfs(list[i]);
    }

    void dfs(int nod) {
        if (been[nod])
            return;
        been[nod] = true;
        for (vector<int>::iterator it = E[nod].begin(); it != E[nod].end(); ++it)
            dfs(*it);

        top.push_back(nod);
    }

    stack<int> S;
    vector< vector<int> > sccs;
    vector<int> index, lowlink, scc;
    int indecs;
    vector< vector<int> > edges_, E;
    vector<int> top;
    vector<bool> been;
};

int main() {
    ifstream cin("drumuri.in");
    ofstream cout("drumuri.out");

    int N, M; cin >> N >> M;
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        G.addArc(x - 1, y - 1);
    }

    cout << G.kernels();
}
