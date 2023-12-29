// OK 
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
        T = D = S = vector<int>( 4 * N );
        Build( 1, 1, N );
    }
 
    void Update( int x, int y, int v ) 
    {
        Update( 1, 1, N, x, y, v );
    }
 
    int Query() const
    {
        return T[1];
    }
 
 protected:
    void Build( int nod, int st, int dr )
    {
        T[nod] = S[nod] = D[nod] = dr - st + 1;
 
        if ( st != dr )
        {
            int m = ( st + dr ) / 2;
            Build( 2 * nod, st, m );
            Build( 2 * nod + 1, m + 1, dr );
        }
    }
 
    void Set( int nod, int val )
    {
        T[nod] = D[nod] = S[nod] = val;
    }
 
    void PushDown( int nod, int st, int dr )
    {
        if ( T[nod] == 0 )
        {
            Set( 2 * nod, 0 );
            Set( 2 * nod + 1, 0 );
        }
 
        if ( T[nod] == dr - st + 1 )
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
            return;                            // we're lazy: don't bother to update the sons
        }
        
        // we can't be lazy anymore
		PushDown( nod, st, dr ); 

		int m = ( st + dr ) / 2;

		if ( L <= m ) Update( 2 * nod, st, m, L, R, val );
		if ( m < R  ) Update( 2 * nod + 1, m + 1, dr, L, R, val );

		S[nod] = S[2 * nod];
		if ( S[2 * nod] == m - st + 1 )
			S[nod] += S[2 * nod + 1];

		D[nod] = D[2 * nod + 1];
		if ( D[2 * nod + 1] == dr - m )
			D[nod] += D[2 * nod];

		T[nod] = max( T[2 * nod], T[2 * nod + 1] );
		T[nod] = max( T[nod], D[2 * nod] + S[2 * nod + 1] );
    }
    
private:
    vector <int> T, D, S;    // Maxim din tot, maxim la stanga, maxim la dreapta
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
