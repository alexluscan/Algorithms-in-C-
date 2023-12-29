// ok, dar tle pe ultimul test
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int K = 52, Mod = 5000000, MaxVal = 100048, Dim = 10001;

// Binary Indexed Tree
class Bit { 
public:
    Bit(int n = 0) : n {n}, bit {n + 1}
    {}

    int sum(int x) 
    {
        int s = 0;
        for (int i = x; i; i -= i & -i)
        {
            s += bit[i];
            if (s >= Mod)
				s -= Mod;
		}

        return s;
    }
    
    void add(int x, int v) 
    {
        for (int i = x; i <= n; i += i & -i)
        {
            bit[i] += v;
            if (bit[i] >= Mod)
				bit[i] -= Mod;
		}
    }
    
private:
	int n;
	std::vector<int> bit;  
};


std::vector<Bit> aib;   // aib[k][v] = nr de subsiruri crescatoare de lungime k, care se termina cu valoarea v
int Val = 0;         // valoarea maxima a unui elem din sir, dupa normalizare
int v[Dim];          
int map[MaxVal];     // sirul v[] normalizat
int a[Dim];          // sirul v[] sortat 

int main()
{
    int K, N;
    cin >> N >> K;
    
    for (int i = 1; i <= N; ++i) 
    {
		cin >>  a[i];
		v[i] = a[i];
	}
    
    sort(a + 1, a + N + 1);
    
    map[a[1]] = ++Val; //  mapam numerele pe un interval mai mic (1..10k) 
    
    for (int i = 2; i <= N; ++i)
        if (a[i] == a[i - 1]) 
			map[a[i]] = Val;
        else 
			map[a[i]] = ++Val;
	
    aib = std::vector<Bit>(K + 1, Bit(Val));
    
    //  O(N * K * log(N)) 
    for (int i = 0; i < N; ++i)
    {
        int x = map[v[i]];  // noua valoare a lui v[i]        
        aib[1].add(x, 1);   // Oricare numar poate incepe un sir crescator

        for (int k = 2; k <= K; ++k)
        {
            int cnt = aib[k - 1].sum(x - 1);   // Oricare subsir crescator de lungime k - 1 cu ultima valoare mai mica decat x 
            if (cnt)
				aib[k].add(x, cnt);         // poate fi extins la un subsir de lungime k cu x - ultimul element
		}
    }
    
    cout <<  aib[K].sum(Val) << '\n';
    
    return 0;
}
