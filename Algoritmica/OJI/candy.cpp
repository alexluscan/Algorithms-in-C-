#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

VI V1, V2;

void def(VI& A, VI& B)
{
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    B.erase(unique(B.begin(), B.end()), B.end());

    int cnt = 0;
    for (auto x : B)
        cnt += binary_search(A.begin(), A.end(), x);

}

int main()
{
    int n;
    cin >> n;
    V1 = V2 = VI(n);
    for (int i = 0; i < n; ++i)
        cin >> V1[i];
    for (int i = 0; i < n; ++i)
        cin >> V2[i];
    def(V1, V2);
}
