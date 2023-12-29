#include <iostream>
using namespace std;

int a[100], n;

void Update(int p, int val)
{
    for (int i = p; i <= n; i += i & -i)
        a[i] += val;
}

int Query(int p)
{
    int sum = 0;
    for (int i = p; i >= 1; i -= i & -i)
        sum += a[i];
    return sum;
}

int main()
{
    cin >> n;
    int x;
    for (int i = 1; i <= n; ++i)
    {
        cin >> x;
        Update(i, x);
    }
    cout << Query(n);
}
