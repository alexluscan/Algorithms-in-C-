// OK - numerotarea nodurilor de la 0
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("heavypath.in");
ofstream fout("heavypath.out");

using VI  = vector<int>;
using VVI = vector<VI>;

class ST {
  public:
    ST(const VI &values)
    {
        for (N = 1; N < int(values.size()); N <<= 1);  // N = cea mai mica putere a lui 2, mai mare decat size()

        tree = VI(2 * N, 0);    // 4 n
        for (int i = 0; i < int(values.size()); ++i) // valorile innitiale puse pe poz [n, .. 2n -1]
            tree[N + i] = values[i];
        for (int x = N - 1; x > 0; --x)
            tree[x] = max(tree[2 * x], tree[2 * x + 1]);
    }

    void Update(int where, const int value) 
    {
		
        tree[where += N] = value;
        for (where >>= 1; where > 0; where >>= 1)
            tree[where] = max(tree[2 * where], tree[2 * where + 1]);
    }

    int Query(int l, int r) const 
    {
        l += N;  r += N;
        int vmax = 0;
        while (l <= r) 
        {
            vmax = max(vmax, max(tree[l], tree[r]));
            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }
        return vmax;
    }

  private:
    int N;
    VI tree;
};

VVI T, paths; // graful, lanturile
int N;
VI v, t, nr, h;
VI pId; // pID[x] - id-ul lantului in care se gaseste x
VI pos; // pos[x] = poz lui x in lantul sau
vector<ST> st;

void DFS(const int x) 
{
    int hs(-1);
    nr[x] = 1;
    for ( const auto& y : T[x] )
    {
        if (y == t[x])
            continue;
        t[y] = x;
        h[y] = h[x] + 1;
        DFS(y);
        nr[x] += nr[y];
        if (hs == -1 || nr[y] > nr[hs])
            hs = y;
    }
    if (hs == -1 ) // frunza
    {
        pId[x] = int(paths.size()); // incepem un nou path
        paths.push_back(VI());
    } 
    else 
        pId[x] = pId[hs];
    
    pos[x] = int(paths[pId[x]].size()); // va fi pus la sfarsit (vechea poz n)
    paths[pId[x]].push_back(x);
}

void BuildHeavyPath() 
{
    t = pId = VI(N, -1);  
    nr = VI(N);           // nr[i] - ne noduri din subarb cu rad in i
    h = VI(N, -1);        // adancimea in Dfs
    pos = VI(N, -1);      // pos[x] = poz in lantul curent  a nodului x
    h[0] = 0;
    DFS(0);

	for (int p = 0; p < int(paths.size()); ++p) 
	{
        VI pathValues; 
        
        for (int x : paths[p])
            pathValues.push_back(v[x]); // plasam in ST valori, nu etichete de noduri
     
        st.push_back(ST(pathValues));
    }
    
}

int Query(int x, int y) 
{
    if (pId[x] == pId[y]) 
    {
        if (pos[x] > pos[y])  // x sa fie mai jos in lant
            swap(x, y);
        return st[pId[x]].Query(pos[x], pos[y]);
    }
    if (h[paths[pId[x]].back()] < h[paths[pId[y]].back()])
        swap(x, y);
    return max(st[pId[x]].Query(pos[x], int(paths[pId[x]].size()) - 1), 
                          Query(t[paths[pId[x]].back()], y));
}

int main() 
{
    int Q;
    fin >> N >> Q;
    v = VI(N);
	T = VVI(N);
    for (int x = 0; x < N; ++x)
        fin >> v[x];
   
    
    for (int e = 1; e < N; ++e) 
    {
        int x, y;
        fin >> x >> y;
        x--,  y--;
        T[x].push_back(y);
        T[y].push_back(x);
    }
    
    BuildHeavyPath();
    
    int op, x, y, val;
    for (; Q > 0; --Q) 
    {
        fin >> op;
        if (op == 0) 
        {
            fin >> x >> val;
            v[x] = val;
            st[pId[x - 1]].Update(pos[x - 1], val);
        } 
        else 
        {
            fin >> x >> y;
            fout << Query(x - 1, y - 1) << "\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}
