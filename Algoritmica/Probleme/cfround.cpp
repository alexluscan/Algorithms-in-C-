#include <iostream>
using namespace std;

long long n;

int main()
{
    long long x;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> x;
        if (x % 2)
        {
            cout << "2\n";
            continue;
        }
        else
        {
            while (x % 2 == 0)
                x /= 2;
            if (x > 1)
                cout << x << '\n';
            else
                cout << "-1\n";
        }
    }
}

