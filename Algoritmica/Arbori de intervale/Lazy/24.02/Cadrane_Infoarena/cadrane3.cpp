#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
 
using namespace std;
 
ifstream fin("cadrane.in");
ofstream fout("cadrane.out");
 
int n;
 
pair<int, int> points[100005];
 
vector<int> vec, vecCols[100005];
int cntLines[100005];
 
set<int> setLines, setCols;
 
int binarySearch(int x) {
 
    int left = 0, right = vec.size() - 1;
    while (left <= right) {
 
        int mid = (left + right) / 2;
 
        if (vec[mid] == x)
            return mid;
        if (vec[mid] > x)
            right = mid - 1;
        else
            left = mid + 1;
 
    }
 
}
 
int lineCount;
void normLines(void) {
 
    vec.clear();
    for (set<int>::iterator it = setLines.begin(); it != setLines.end(); ++it)
        vec.push_back(*it);
 
    lineCount = vec.size();
 
    for (int i = 1; i <= n; ++i) {
 
        points[i].first = binarySearch(points[i].first) + 1;
 
        cntLines[points[i].first]++;
 
    }
}
 
int colCount;
void normCols(void) {
 
    vec.clear();
    for (set<int>::iterator it = setCols.begin(); it != setCols.end(); ++it)
        vec.push_back(*it);
 
    colCount = vec.size();
 
    for (int i = 1; i <= n; ++i) {
 
        points[i].second = binarySearch(points[i].second) + 1;
 
        vecCols[points[i].second].push_back(points[i].first);
 
    }
}
 
struct Aint {
    int min, add;
    Aint() {
        min = add = 0;
    }
} aint[400005];
 
void build(int node, int left, int right, int pos, int val) {
 
    if (left > right)
        return;
 
    if (left == right && left == pos) {
 
        aint[node].min = val;
        return;
 
    }
 
    int mid = (left + right) / 2;
 
    if (mid >= pos)
        build(2 * node, left, mid, pos, val);
    else
        build(2 * node + 1, mid + 1, right, pos, val);
 
    aint[node].min = min(aint[2 * node].min, aint[2 * node + 1].min);
 
}
 
void update(int node, int left, int right, int uLeft, int uRight, int val) {
 
    if (uLeft <= left && right <= uRight) {
 
        aint[node].min += val;
        aint[node].add += val;
        return;
 
    }
 
    aint[2 * node].min += aint[node].add;
    aint[2 * node + 1].min += aint[node].add;
    aint[2 * node].add += aint[node].add;
    aint[2 * node + 1].add += aint[node].add;
    aint[node].add = 0;
 
    int mid = (left + right) / 2;
 
    if (uLeft <= mid)
        update(2 * node, left, mid, uLeft, uRight, val);
    if (mid + 1 <= uRight)
        update(2 * node + 1, mid + 1, right, uLeft, uRight, val);
 
    aint[node].min = min(aint[2 * node].min, aint[2 * node + 1].min);
 
}
 
int main() {
 
    fin >> n;
 
    for (int i = 1; i <= n; ++i) {
 
        fin >> points[i].second >> points[i].first;
 
        setLines.insert(points[i].first);
        setCols.insert(points[i].second);
 
    }
 
    normLines();
    normCols();
 
    for (int i = 0; i <= 4 * lineCount; ++i)
        aint[i].min = 1000000000;
 
    for (int i = lineCount, curr = 0; i; --i) {
 
        curr += cntLines[i];
 
        build(1, 1, lineCount, i, curr);
 
    }
 
    int sol = 0;
    for (int col = 1; col <= colCount; ++col) {
 
        for (vector<int>::iterator it = vecCols[col].begin(); it != vecCols[col].end(); ++it)
            update(1, 1, lineCount, 1, *it, -1);
 
        sol = max(sol, (int)vecCols[col].size() + aint[1].min);
 
        for (vector<int>::iterator it = vecCols[col].begin(); it != vecCols[col].end(); ++it)
            update(1, 1, lineCount, *it, lineCount, 1);
 
    }
 
    fout << sol << '\n';
 
    return 0;
 
}
