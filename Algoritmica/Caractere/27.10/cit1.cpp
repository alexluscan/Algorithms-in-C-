// Citirea intregului fisier si plasarea continutului intr-un sir
#include <fstream>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char a[10000];
	fin.getline(a, 10000, EOF);   // EOF - End Of File 
	
	fout << a;
	return 0;
}
