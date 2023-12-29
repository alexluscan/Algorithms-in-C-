// O(n + m)
#include <fstream>
#include <vector>
#include <stack>
#include <bitset>
#define INF 0x3f3f3f3f
using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

using VI  = vector<int>;
using VVI  = vector<VI>;

int n, m, a, b;
int nv;
VVI G, cc;
VI niv, L, c;
bitset<1000000> inStack;
stack<int> stk;

void Tarjan(int nod);

int main()
{
    fin >> n >> m;
    
    G = VVI(n + 1);
    niv = L = VI(n + 1);
    
    for ( int i = 1; i <= m; ++i )
    {
        fin >> a >> b;
        G[a].push_back(b);
    }
    
    for ( int i = 1; i <= n; ++i )
        if ( niv[i] == 0 )
            nv = 0, Tarjan(i);
    
    fout << cc.size() << "\n";
  
	for (const auto& c : cc)
    {
		for (const auto& x : c)
			fout << x << ' ';
		fout << '\n';
	}  
	
    fin.close();
    fout.close();
    return 0;
}

void Tarjan(int x)
{
    niv[x] = L[x] = ++nv;
    stk.push(x);
    inStack[x] = true;
    
    for ( const auto& y : G[x] )
        if ( niv[y] == 0 ) // muchie de arbore
        {
            Tarjan(y);
            L[x] = min(L[x], L[y]);
        }
        else  // sa fie muchie de intoarcere, nu muchie transversala
            if ( inStack[y] )
                L[x] = min(L[x], niv[y]);
    
    // daca x e radacina comp tare conexe, scoatem din stiva componenta curenta (stiva nu se goleste neaparat)
    if ( niv[x] == L[x] )
    {
        c.clear();
        int x2;
        while ( true )
        {
            c.push_back(x2 = stk.top());
            stk.pop();
            inStack[x2] = false;
            if ( x2 == x ) 
				break;
        } 
        cc.push_back(c);
    }
}
