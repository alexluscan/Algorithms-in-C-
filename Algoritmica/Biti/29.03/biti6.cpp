// Generarea submultimilor unei multimi cu n elemente
#include <iostream>
using namespace std;



int main()
{
	int n;
	cin >> n;
	
	for (int msk = 0; msk < (1 << n); ++msk) // generez toate submultimile de biti
	{
		for (int i = 0; i < n; ++i)
			if (msk & (1 << i)) // daca bitul i este in masca msk
				cout << i + 1 << ' ';
		cout << '\n';
	}

}
