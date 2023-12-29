#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("platforma.in");
ofstream fout ("platforma.out");

#define int long long

int cer, n, a[15005], sol[15005];

main()
{
    fin >> cer >> n;
    if (cer == 1)
    {
        for (int i = 1; i <= n; ++i)
            fin >> a[i];
        int i = 1;
        bool ok = true;
        while (i <= n && ok)
        {
            if (a[i] != i)
            {
                --i;
                int j = i;
                while (i <= (2 * j - 1))
                {
                    if (a[i] != a[j])
                    {
                        ok = false;
                        break;
                    }
                    ++i;
                }
                --i;
            }
            ++i;
        }
        fout << ok;
    }
    if (cer == 2)
    {
        sol[0] = 0;
        sol[1] = 0;
        sol[2] = 0;
        sol[3] = 1;
        for (int i = 4; i <= n; ++i)
        {
            if (i % 2 == 1)
                sol[i]++;

        }
    }
}
