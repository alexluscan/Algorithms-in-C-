#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

ifstream fin("flowers.in");
ofstream fout("flowers.out");

int n, m, k, t;
int cuplaj;
bool am_cuplaj = 1;

vector<int> R, L, s;
vector<vector<int>> S;
vector<vector<bool>> e;
bitset<500> v;

void Read();
bool Match(int x);

int main()
{
    fin >> t;
    while( t-- )
    {
        Read();
        k = 0;
        do
        {

            cuplaj = 0;
            L = R = vector<int>(n + 1);
            do
            {
                am_cuplaj = false;
                v.reset();
                for ( int i = 1; i <= n; i++ )
                    if ( !L[i] && Match(i) )
                    {
                        am_cuplaj = true;
                        cuplaj++;
                    }

            } while ( am_cuplaj );

            if ( cuplaj == n )
            {
                k++;
                for ( int i = 1; i <= n; i++ )
                {
                    e[R[i]][i] = 1;
                    s.push_back(R[i]);
                }


                S.push_back(s);
                s.clear();
            }
        } while(cuplaj == n);


        fout << k << '\n';
        for ( auto y : S )
        {
            for ( auto x : y )
                fout << x << ' ';
            fout << '\n';
        }
        S.clear();
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

void Read()
{
    fin >> n >> m;

    int x;

    e = vector<vector<bool>>(n + 1);
    for ( int i = 1; i <= n; i++ )
         e[i] = vector<bool>(n + 1);

    for ( int i = 1; i <= m; i++ )
    {
        for ( int j = 1; j <= n; j++ )
        {
            fin >> x;
            e[x][j] = true;
        }
    }

}

bool Match(int x)
{
    if ( v[x] )
        return false;
    v[x] = 1;

    for (int i = 1; i <= n; i++ )
        if ( !e[x][i] )
            if( !R[i] || Match(R[i]) )
            {

                R[i] = x;
                L[x] = i;
                return true;
            }
    return false;
}
