#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXSIZE 1000

FILE *in, *out, *ok;
char Ans1[MAXSIZE+10], Ans2[MAXSIZE+10];
int L1, L2;

inline void afis(int nr, char *S)
{
	printf("%d %s\n", nr, S);
	exit(0);
}

inline int modul(int X)
{
	if (X < 0) return -X;
	return X;
}

int main()
{
	in = fopen("2d.in","r");
	out = fopen("2d.out","r");
	ok = fopen("2d.ok","r");
	
	if (in == NULL)
		afis(0, "Nu exista fisier de intrare!");
	if (out == NULL)
		afis(0, "Nu exista fisier de iesire!");
	if (ok == NULL)
		afis(0, "Nu exista fisier .ok !");
	
	fgets(Ans1, MAXSIZE, out);
	fgets(Ans2, MAXSIZE, ok);
	
	L1 = strlen(Ans1);
	while (L1 >= 0 && (Ans1[L1] < '0' || Ans1[L1] > '9'))
		--L1;
	
	L2 = strlen(Ans2);
	while (L2 >= 0 && (Ans2[L2] < '0' || Ans2[L2] > '9'))
		--L2;	
	
	if (L1 != L2)
		afis(0, "Raspuns incorect sau precizie incorecta");
	
	for (int i = 0; i < L1; ++i)
		if (Ans1[i] != Ans2[i])
			afis(0, "Raspuns incorect");
	
	if (modul(Ans1[L1] - Ans2[L2]) > 1)
		afis(0, "Raspuns incorect");
	
	afis(5, "Corect");
	
	return 0;
}