// OK - infoarena
#include <fstream>
#include <vector>
using namespace std;

ofstream fout("dijkstra.out");

//===============================================
class Heap {
	using  VI = vector<int>;
public:
	Heap(int n = 0, const VI& D = VI(1)) : 
		nH {0}, 
		H  {VI(n + 1)}, 
		P  {VI(n + 1)},
		D  {D}
	{}
	
	void pop(int node = -1) 
	{
		int p;
		if ( node == -1 )  // stergem minimul ( H[1] )
			p = 1;
		else
			p = P[node];   // stergem alt nod
		
		Swap(p, nH--);
		int s = 2 * p;
		while ( s <= nH ) 
		{
			if ( s + 1 <= nH && D[H[s + 1]] < D[H[s]] )
				s++;
			if ( D[H[s]] < D[H[p]] )
			{				
				Swap(s, p);	
				p = s;	
				s = 2 * p;
			}
			else break;
		}
	}
	
	void push(int node) 
	{
		H[++nH] = node;	P[node] = nH;
		up(node);
	}
	
	void up(int node) 
	{
		int s = P[node], p = s / 2;
		while ( p != 0 && D[H[s]] < D[H[p]] ) 
		{
			Swap(p, s);	
			s = p; p = s / 2;
		}
	}
	
	bool empty() const
	{
		return nH <= 0;
	}
	
	int top() const
	{
		return H[1];
	}
	
private:
	void Swap(int s, int p) 
	{
		swap(H[s], H[p]);
		P[H[p]] = p;
		P[H[s]] = s;
	}
	
	int nH;
	VI H, P;      // P = poz in heap
	const VI &D;  // obligatoriu referinta, altfel D e o copie a lui ::D
};

//===============================================

using VI  = vector<int>;
using VVP = vector<vector<pair<int, int>>>;

const int Inf = 0x3f3f3f3f;
int n, m;
VVP G; 
VI D;

void Read();
void Write(const VI& D);
void Dijkstra(int k, VI& D);

int main()
{
	Read();
	Dijkstra(1, D);
	Write(D);

	fout.close();
	return 0;
}

void Dijkstra(int x, VI& D)
{
	bool inHeap;
	int y, w;
	D = VI(n + 1, Inf);
	D[x] = 0;
	Heap heap(n, D);
	heap.push(x);
	
	while ( !heap.empty() )
	{
		x = heap.top();
		heap.pop();
		for (const auto& p : G[x])
		{
			y = p.first, w = p.second;
			if ( D[y] > D[x] + w) // daca y a iesit inainte din heap, conditia nu poate fi adevarata
			{
				inHeap = D[y] != Inf; // deci y poate fi doar in heap sau cu D[y] = Inf
				D[y] = D[x] + w;
				if ( inHeap )
					heap.up(y);
				else
					heap.push(y);
			}
		}
	}
}

void Read()
{
	ifstream fin("dijkstra.in");
	int a, b, cost;
	fin >> n >> m;
	G.resize(n + 1);
	for (int i = 0; i < m; ++i)
	{
		fin >> a >> b >> cost;
		G[a].emplace_back(b, cost);
	}
	
	fin.close();
}

void Write(const VI& D)
{
	for (int i = 2; i <= n; ++i )
		if ( D[i] != Inf)
			fout << D[i] << ' ';
		else
			fout << "0 ";
	fout << '\n';
}

