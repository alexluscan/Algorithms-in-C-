/*Se citeste n, apoi numele a n copii.
 * Sa se afiseze copiii in ordine alfabetica
 */  
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("copii.in");
ofstream fout("copii.out");

char c[35][25];
int n;

void Sort();

int main()
{	
	fin >> n;
	fin.get();
	for (int i = 0; i < n; ++i)
		fin.getline(c[i], 25);
		
	Sort();
	
	for (int i = 0; i < n; ++i)
		fout << c[i] << '\n';
	return 0;
}

void Sort()
{
	char aux[25];
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (strcmp(c[i], c[j]) > 0)
			{
				strcpy(aux, c[i]);
				strcpy(c[i], c[j]);
				strcpy(c[j], aux);
			}
}
