#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

constexpr int N = 1e6 + 1;
ifstream fin("dulciuri.in");
ofstream fout("dulciuri.out");


class Aib {
    int aib[N] = {};

   public:
    void Update(int x, int v) 
    {
        for (++x; x < N; x += x & -x) 
			aib[x] += v;
    }
    
    long long Query(int x) 
    {
        long long r = 0;
        for (++x; x; x -= x & -x) 
			r += aib[x];
        return r;
    }
    
    long long Query(int st, int dr) 
    { 
		return Query(dr - 1) - Query(st - 1); 
	}

    double Solve(int st, int dr) 
    {
        if (st > dr) swap(st, dr);
        return st == dr ? Query(st, dr + 1) : Query(st, dr) / double(dr - st);
    }
};

Aib ax, ay;

int main() 
{
    
    int q, op;
    fin >> q;

    while (q--) 
    {
        fin >> op;

        if (op == 1) // indulcire verticala
        {
            int x, v;
            fin >> x >> v;
          
            ax.Update(x, v);
        } 
        else if (op == 2) // indulcire orizontala
        {
            int y, v;
            fin >> y >> v;
            ay.Update(y, v);
        } 
        else 
        {
            int x1, y1, x2, y2;
            fin >> x1 >> y1 >> x2 >> y2;
            fout << fixed << setprecision(10) 
				 << ax.Solve(x1, x2) + ay.Solve(y1, y2) << '\n';
        }
    }
    
    return 0;
} 
