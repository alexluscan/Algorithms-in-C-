
// Olimpiada Judeteana de Informatica, 9 martie 2002
// Clasa a X-a
// Problema 2 (Cod)


#include <stdio.h>
#include <string.h>

#define DIM 200 // Dimensiunea maxima a codului caracteristic al unui organism

#define INPUT_FILE  "COD.IN"
#define OUTPUT_FILE "COD.OUT"

unsigned  char a[DIM + 1], b[DIM + 1], huge p[2*DIM + 2][DIM + 2], huge l[DIM + 1][DIM + 1];

// a si b sunt codurile caracteristice a doua organisme (coduri ce se citesc din fisierul de intrare)
// p este o matrice de caractere, un vector de siruri distincte (subsirurile comune de lungime maxima si posibil de valoare maxima gasite la un moment dat)
// (Observatie: In p[x][0] se retine lungimea sirului x)
// l contine lungimile subsirurilor comune maximale ale sirurilor a si b; l[i][j] = lungimea subsirului comun de lungime maxima (si valoare maxima) a sirurilor n[0 .. i - 1] si m[0 .. j - 1]

unsigned char m, n, i, j, k, q;

// m si n reprezinta lungimile codurilor (sirurilor) a si respectiv b;
// k si q sunt variabile auxiliare

int main()
{
	FILE* f = NULL;
	f = fopen(INPUT_FILE, "rt");

	fscanf(f, "%s\n%s", a, b);

	while(a[m]) ++m;
	while(b[n]) ++n;

  // Programare dinamica (ca la problema clasica: determinarea subsirului comun de lungime maxima a doua siruri; plus cateva adaugiri (matricea p))
	for(i = 1; i <= m; i++)
		for(j = 1; j <= n; j++)
	{
	  if (i % 2 == 1) // Daca i e impar
	  {
		k = DIM + 1;
		q = 0;
	  }
	  else // Daca i e par
	  {
		k = 0;
		q = DIM + 1;
	  }

	  if(a[i - 1] == b[j - 1]) // (1) Daca pe pozitiile i - 1 in sirul n si j - 1 in sirul m e acelasi caracter
	  {
		l[i][j] = l[i - 1][j - 1] + 1; // Lungimea subsirului comun (dintre sirurile n[0 .. i - 1] si m[0 .. j - 1]) de lungime maxima creste cu 1
		memcpy(p[k + j], p[q + j - 1], sizeof(p[0][0]) * (p[q + j - 1][0] + 1)); // Se pastreaza drept CMLSC de valoare maxima sirul p[q + j - 1] plus caracterul n[i - 1]
		++p[k + j][0]; // Se incrementeaza lungimea sirului p[k + j]
		p[k + j][ p[k + j][0] ] = a[i - 1]; // Pe ultima pozitie se adauga caracterul n[i - 1]
	  }
	  else if(l[i][j - 1] > l[i - 1][j]) // (2)
	  {
		l[i][j] = l[i][j - 1];
		memcpy(p[k + j], p[k + j - 1], sizeof(p[0][0]) * (p[k + j - 1][0] + 1)); // Se pastreaza drept CMLSC de valoare maxima sirul p[k + j - 1]
	  }
	  else if(l[i][j - 1] < l[i - 1][j]) // (3)
	  {
		l[i][j] = l[i - 1][j];
		memcpy(p[k + j], p[q + j], sizeof(p[0][0]) * (p[q + j][0] + 1)); // Se pastreaza drept CMLSC de valoare maxima sirul p[q + j]
	  }
	  else if(memcmp(p[k + j - 1], p[q + j], DIM + 1) > 0) // Daca l[i][j - 1] == l[i - 1][j] se compara sirurile si se pastreaza (in matricea p) cel de valoare maxima
		   {
			  l[i][j] = l[i][j - 1];
			  memcpy(p[k + j], p[k + j - 1], sizeof(p[0][0]) * (p[k + j - 1][0] + 1)); // Se pastreaza drept CMLSC de valoare maxima sirul p[k + j - 1]
			}
			else
			{
			   l[i][j] = l[i - 1][j];
			   memcpy(p[k + j], p[q + j], sizeof(p[0][0]) * (p[q + j][0] + 1));  // Se pastreaza drept CMLSC de valoare maxima sirul p[q + j]
			}
	// Relatiile (1), (2) si (3) sunt clasice (cele de la problema clasica)
	// Relatiile (2) si (3): l[i][j] = lungimea CLMSC dintre n[0 .. i - 1] si m[0 .. j - 1] = lungimea celui mai lung subsir dintre CMLSC dintre n[0 .. i - 1] si m[0 .. j - 2] si
	// CMLSC dintre n[0 .. i - 2] si m[0 .. j - 1]

	}

  if(m % 2 == 1)
  {
	k = DIM + 1;
  }
  else // Daca m e par
  {
	k = 0;
  }

  f = fopen(OUTPUT_FILE, "wt");
  fprintf(f, "%s", p[k + n] + 1);  // primul element pe linie nu trebuie listat
								   // el reprezinta dim sirului
  return 0;
}
