/* Se citeste un cuvant c si un text a;
 * Sa se stearga toate aparitiile cuvantului c din textul a
 */ 
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text2.in");
ofstream fout("text2.out");

int main()
{	
	char a[1000];
	char aux[1000];
	char c[20];  // cuvantul
	
	fin >> c;
	int n = strlen(c);
	fin.get(); // extrag primul newline
	
	fin.getline(a, 1000, EOF);

	char *p = strstr(a, c);
	while (p) 
	{
		strcpy(aux, p + n);
		strcpy(p, aux);
		p = strstr(p, c);
	}
		
	fout << a;
	return 0;
}
