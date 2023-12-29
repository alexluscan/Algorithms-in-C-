#include <fstream>
using namespace std;

ifstream fin ("datorii.in");
ofstream fout ("datorii.out");

int aib[5 + 15000];
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
	int x, y, m;
	bool t;
	
	fin >> n >> m;
	
	for (int i = 1; i <= n; ++i)
	{
		fin >> x;
		Update(i, x);
	}
	
	for (int i = 1; i <= m; ++i)
	{
		fin >> t >> x >> y;
		
		if (!t) 
			Update(x, -y);
		else
			fout << Query(y)- Query(x - 1) << '\n';
	}
	
	fin.close();
	fout.close();
	return 0;
}

