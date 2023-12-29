#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char a[10000];
	
	fin.getline(a, 10000, EOF);
	
	int lit_mari = 0, lit_mici = 0, cifre = 0;
	
	for (int i = 0; a[i]; i++)
	{
		if (a[i] >= 'A' && a[i] <= 'Z')
			lit_mari++;
		
		if (a[i] >= 'a' && a[i] <= 'z')
			lit_mici++;
			
		if (a[i] >= '0' && a[i] <= '9')
			cifre++;
	}
	
	
	fout << lit_mari << " litere_mari\n"
		 << lit_mici << " litere mici\n"
		 << cifre    << " cifre";
	return 0;
}
