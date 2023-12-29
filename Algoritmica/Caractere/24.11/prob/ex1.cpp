/* Se citeste un cuvant c si un text a;
 * Sa se numere toate aparitiile cuvantului c in textul a
 */ 
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text2.in");
ofstream fout("text2.out");

int main()
{	
	char a[1000];
	char c[20];  // cuvantul
	
	fin >> c;
	int n = strlen(c);
	fin.get(); // extrag primul newline
	
	fin.getline(a, 1000, EOF);
	
	int cnt {0};
	for (char *p = strstr(a, c); p; p = strstr(p + n, c))
		cnt++;
		
	fout << cnt;
	return 0;
}
