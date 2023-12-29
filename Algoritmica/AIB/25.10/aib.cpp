#include <fstream>
using namespace std;

int aib[10000];
int n;


// a[i] += val
void Update(int p, int val)
{
	for (int i = p; i <= n; i += i & -i)
		aib[i] += val;
}

// a[1] + ... + a[i]
int Query(int p)
{
	int suma = 0;
	for (int i = p; i >= 1; i -= i & -i)
		suma += aib[i];
		
	return suma;
}

int main()
{
	
}

