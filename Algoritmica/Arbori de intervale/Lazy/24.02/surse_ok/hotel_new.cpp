// NOO!
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
 
class ST
{
public:
    ST( int _N )
    {
        N = _N;
        Max = maxR = maxL = vector<int>( 4 * N );
        flag = vector<int>(4 * N, -1);
        ok = vector<bool>(4 * N);
        Build( 1, 1, N );
    }
 
    void Update( int x, int y, int v ) 
    {
        Update( 1, 1, N, x, y, v );
    }
 
    int Query() const
    {
        return Max[1];
    }
 
 protected:
    void Build( int nod, int st, int dr )
    {
        Max[nod] = maxL[nod] = maxR[nod] = dr - st + 1;
 
        if ( st != dr )
        {
            int m = ( st + dr ) / 2;
            Build( 2 * nod, st, m );
            Build( 2 * nod + 1, m + 1, dr );
        }
    }
 
    void Set( int nod, int val )
    {
        Max[nod] = maxR[nod] = maxL[nod] = val;
    }
 
    void PushDown( int nod, int st, int dr )
    {
        if ( Max[nod] == 0 )
        {
            Set( 2 * nod, 0 );
            Set( 2 * nod + 1, 0 );
        }
 
        if ( Max[nod] == dr - st + 1 )
        {
            int m = ( st + dr ) / 2;
            Set( 2 * nod, m - st + 1 );
            Set( 2 * nod + 1, dr - m );
        }
    }
	
    void Update( int nod, int st, int dr, int L, int R, int val )
    {
        if ( L <= st && dr <= R )
        {                                           
            Set( nod, ( dr - st + 1 ) * val ); // update just current node
            flag[nod] = val;
            ok[nod] = true;
            return;                            // we're lazy: don't bother to update the sons
        }
        ok[nod] = false; 
		int m = ( st + dr ) / 2;

		if ( L <= m ) Update( 2 * nod, st, m, L, R, val );
		if ( m < R  ) Update( 2 * nod + 1, m + 1, dr, L, R, val );

		if ( !ok[nod] )
		{
			maxL[nod] = maxL[2 * nod];
			if ( maxL[2 * nod] == m - st + 1 )
				maxL[nod] += maxL[2 * nod + 1];

			maxR[nod] = maxR[2 * nod + 1];
			if ( maxR[2 * nod + 1] == dr - m )
				maxR[nod] += maxR[2 * nod];

			Max[nod] = max( Max[2 * nod], Max[2 * nod + 1] );
			Max[nod] = max( Max[nod], maxR[2 * nod] + maxL[2 * nod + 1] );
		}		
    }
    
private:
    vector <int> Max, maxR, maxL, flag;
    vector<bool> ok;
    int N;
};
 
int n, m, op, i, L;
 
int main()
{
    ifstream fin("hotel.in");
    ofstream fout("hotel.out");
 
    fin >> n >> m;

    ST s(n);
	
    while ( m-- )
    {
        fin >> op;
      
        if ( op == 1 )
        {
            fin >> i >> L;
            s.Update( i, i + L - 1, 0 );
        }
 
        if ( op == 2 )
        {
            fin >> i >> L;
            s.Update( i, i + L - 1, 1 );
        }

        if ( op == 3 )
            fout << s.Query() << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
