// Citirea intregului fisier CUVANT cu CUVANT 
// /daca separatorii intre cuvinte sunt spatii si newline
#include <fstream>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char cuv[20];
	
	while (fin >> cuv)
	{
		fout << cuv << '\n';
	}
	
	return 0;
}
