// accepted
#include <algorithm>
#include <iostream>
using namespace std;


const int K = 52, Mod = 5000000, MaxVal = 100048, Dim = 10001;

int aib[K][Dim];     // aiv[k][v] = nr de subsiruri crescatoare de lungime k, care se termina cu valoarea v
int Val = 0;         // valoarea maxima a unui elem din sir, dupa normalizare
int v[Dim];          
int map[MaxVal];     // sirul v[] normalizat
int a[Dim];          // sirul v[] sortat 


int Query(int *b, int x)
{
    int sum = 0;
    for (int i = x; i; i -= (i & -i)) 
    {
		sum += b[i];
		if (sum >= Mod) 
			sum -= Mod;
	}
    return sum;
}

void Update(int *b, int x, int v)
{
    for (int i = x; i <= Val; i += (i & -i)) 
    {
		b[i] += v;
		if (b[i] >= Mod) 
			b[i] -= Mod;
	}
}

int main()
{
    int K, N;
    cin >> N >> K;
    
    for (int i = 0; i < N; ++i) 
    {
		cin >>  a[i];
		v[i] = a[i];
	}
    
    sort(a, a + N);
    
    map[a[0]] = ++Val; //  mapam numerele pe un interval mai mic (1..10k) 
    
    for (int i = 1; i < N; ++i)
        if (a[i] == a[i - 1]) 
			map[a[i]] = Val;
        else 
			map[a[i]] = ++Val;

    
    //  O(N * K * log(N)) 
    for (int i = 0; i < N; ++i)
    {
        int x = map[v[i]];  // noua valoare a lui v[i]
        
        Update(aib[1], x, 1);   // Oricare numar poate incepe un sir crescator
       
        for (int k = 2; k <= K; ++k)
        {
            int cnt = Query(aib[k - 1], x - 1);   // Oricare subsir crescator de lungime k - 1 cu ultima valoare mai mica decat x 
            if (cnt)
				Update(aib[k], x, cnt);         // poate fi extins la un subsir de lungime k cu x - ultimul element
		}
    }
    
    cout <<  Query(aib[K], Val) << '\n';
    return 0;
}
