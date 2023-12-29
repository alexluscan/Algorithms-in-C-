// O(Q * log(n) * log(k))
/*
 * 
    Se da un sir de n numere naturale si q query-uri. Queryurile pot fi de forma
		0 p x   -> sir[p] devine x
		1 l r k -> cate numere < k se afla in intervalul [l r]
	 
 Solutie:
	Daca valorile sunt naturale, se poate face cu aib 2D in O(Q * log(n) * log(k)) / query

	Daca a[i] = x, acesta poate fi un punct in plan de coordonate (i, a[i])
	Atunci aib[i][a[i]] = nr de valori in intervalul [1...i] care sunt mai mici sau egale cu a[i], 
	sau cate puncte in plan sunt in dreptunghiul (0, 0) , (i, a[i])

	Daca valorile sunt mari, se pot retine query-urile offline, si se normalizeaza valorile, (dar si valorile k !)
	Conteaza doar relatia de inegalitate dintre valori si nu marimile lor propriuzise.
 */ 
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("maxk.in");
ofstream fout("maxk.out");


const int MaxN = 300;
int aib[MaxN + 10][MaxN + 10];  /// aib[i][a[i]] - nr de valori din sir <= a[i] in intervalul de pozitii [1..i]

void update(int X, int Y, int val)
{
    for (int x = X; x <= MaxN; x += x & -x)
		for (int y = Y; y <= MaxN; y += y & -y)
            aib[x][y] += val;
}

int query(int X, int Y)
{
    int sum = 0;
    for (int x = X; x > 0; x -= x & -x)
        for (int y = Y; y > 0; y -= y & -y)
            sum += aib[x][y];
    return sum;
}

int main()
{
	int n, qr;
	
	
    int op, poz, x, L, R, k;

    fin >> n >> qr;
    vector<int> a(n + 1);                // sirul dat
    
    for (int i = 1; i <= n; ++i)
    {
		fin >> x;
		a[i] = x;
		update(i, x, 1);
	}    
	
	// rezolvare offline 
	vector<tuple<int, int, int, int>> Q; // vector de query-uri
	
    while (qr--)
    {
        fin >> op;
        if (op == 0)
        {
			fin >> poz >> x;
			Q.emplace_back(op, poz, x, 0);
		}
		else
		{
			fin >> L >> R >> k;
			Q.emplace_back(op, L, R, k);
		}
    }
    
    // Aici NORMALIZARE pentru valorile din sir (daca e cazul)
    // apoi, normalizare pentru k
  
    for (auto const & q : Q)    // 
    {
		auto [op, A, B, C] = q;
	//	fout << op << ' ' << A << ' ' << B <<  ' ' << C << '\n';
		if (op == 0)
		{
			int i = A, x = B;
			update(i, a[i], -1); // eliminam vechea valoare din sir
			update(i, x, 1);     // updatam cu noua valoare
			a[i] = x;
		}
		else
		{
			int L = A, R = B, k = C;
			int nr = query(R, k - 1);     // cate < k in intervalul [1...R]
			int nl = query(L - 1, k - 1); // cate < k in intervalul [1...L - 1]
			fout << nr - nl << '\n';
		}
    }
    
//	for (int i = 1; i <= n; ++i)
//		fout << a[i] << ' ';
    return 0;
}
