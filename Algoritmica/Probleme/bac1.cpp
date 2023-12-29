/* Generarea Tuturor Submultimilor unei multimi
 * in ordine lexicografica
 *
 * Ex: A = {1, 2, 3, 4}
 * {1} U {2} U {3} U {4}
 * ........
 * {2, 4} U {1} U {3}
 * .......
 *
 */
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

ifstream fin("part_multime.in");
ofstream fout("part_multime.out");

int n;
int x[15];   // x[k] = i (plasam elementul k in submultimea i a partitiei curente)
int nrsol = 1;

void PartMult(int k, int vmax);
void Write(int k, int vmax);

int main()
{
	cin >> n;
	PartMult(1, 0);

	cout << nrsol << " solutii!" << '\n';

}

void PartMult(int k, int vmax) // vmax - val maxima din sirul x[] pana la poz k - 1
{
	if (k > n)
	{
		Write(n, vmax);
		return;
	}
	for (int i = 1; i <= vmax + 1; ++i) // i - partitia in care il pun pe k
	{
		x[k] = i;

		PartMult(k + 1, max(vmax, i));
	}
}

void Write(int k, int vmax)
{
	nrsol++;
	for (int subm = 1; subm <= vmax; ++subm)
	{
		cout << "{ ";

		for (int elem = 1; elem <= n; ++elem)
			if (x[elem] == subm)
				cout << elem << " ";
		cout << "} ";
	}

	cout << '\n';
}










