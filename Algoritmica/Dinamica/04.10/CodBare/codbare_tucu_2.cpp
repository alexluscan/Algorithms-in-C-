#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAX_N = 1801;
ifstream fin("codbare.in");
ofstream fout("codbare.out");

void Debug();
int n;
int c[MAX_N][2][3]; // c[i][j][k] nr de coduri bare de lungime i,
                    // care se termina cu bara j (0 (alb) sau 1 (negru))
                    // de lungime k
int main()
{
    fin >> n;
    c[0][1][1] = 1;
    for ( int i = 1; i < n; ++i )
    {
		for (int j = 0; j < 2; ++j)
		{
			c[i][j][1] = c[i - 1][1 - j][1] + c[i - 1][1 - j][2] + c[i - 1][1 - j][3];
			c[i][j][2] = c[i - 1][j][1];
			c[i][j][3] = c[i - 1][j][2];
		}
    }

    fout << c[n - 1][1][1] + c[n - 1][1][2] + c[n - 1][1][3] << '\n' << '\n';;
//    Debug();
    fin.close();
    fout.close();
    return 0;
}

void Debug()
{
    for ( int i = 0; i < n; ++i )
    {
        for ( int j = 0; j < 2; ++j )
        {
            for ( int k = 1; k <= 3; ++k )
                fout << setw(3) << c[i][j][k];
            fout << '\n';
        }
        fout << '\n';
    }
}
