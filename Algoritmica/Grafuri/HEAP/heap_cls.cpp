
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMax 200001

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

vector<int> D;

// plasam in heap (H) pozitii din sirul D 
class Heap {
public:
	Heap(int n = 0) : nH(0), H(vector<int>(n + 1)), P(vector<int>(n + 1))
	{}
	void pop(int x) 
	{
		int p = P[x], s = 2 * p;
		Swap(p, nH--);
		
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
	
	void push(int x)  // x - pozitie in D
	{
		H[++nH] = x; P[x] = nH;
		up(x);
	}
	
	void up(int x) 
	{
		int s = P[x], p = s / 2;
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
	vector<int> H, P;
};


int main()
{
	int p(0), cod, x, m;
    
    fin >> m;
    D = vector<int>(m + 1);
	Heap heap(m);    
    
    for (int i = 1; i <= m; ++i)
    {
        fin >> cod;
        if ( cod == 3 )
        {
            fout << D[heap.top()] << '\n';
            continue;
        }
        fin >> x;
        if (cod == 1)
        {
            D[++p] = x;
            heap.push(p);
		}

        if ( cod == 2 )
			heap.pop(x);
    }
    
    fin.close();
    fout.close();
    return 0;
}
