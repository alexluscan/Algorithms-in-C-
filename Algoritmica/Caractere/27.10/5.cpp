#include <fstream>
using namespace std;

ifstream fin("copii.in");
ofstream fout("copii.out");

int main()
{	
	int n;
	char c[100];
	
	fin >> n;
	// Extragem Newline ramas dupa n
	fin.get();       // extrage un singur caracter (grafic sau negrafic)
	for (int i = 0; i < n; ++i)
	{
		fin.getline(c, 100);
		fout << c << '\n';
	}
	return 0;
}
