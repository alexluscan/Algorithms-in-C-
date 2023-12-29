#include <fstream>
#include <cstring>
using namespace std;

#define Max 100
#define INF 0x3f3f3f3f

#define IN "pal.in"
#define OUT "pal.out"

char s[Max + 1];  // sirul de caractere
int n;            // lungimea sirului
int nrp[Max];     // nrp[i] nr min de palindr in care se 
                  // poate descompune sirul intre poz [1..i]   
                  
bool Palindrom(int st, int dr);
void Write();
void Dynamic();
void Read();

int main()
{ 
    Read();
    Dynamic();
    Write();
    return 0; 
}
  
void Read()
{ 
    ifstream fin(IN);
    fin >> s;    
    n = strlen(s);
    fin.close();
}

bool Palindrom(int st, int dr)
{
    while (st < dr)
    {
        if (s[st] != s[dr]) return false;
        st++; dr--;
    }
  return true;
}

void Dynamic() // O(n^3)
{
    for ( int i = 0; i < n; i++ )
        if ( Palindrom(0, i) ) nrp[i] = 1;
        else
        {
            nrp[i] = INF;
            for (int j = 0; j < i; j++)
                if ( Palindrom(j + 1, i) && nrp[j] + 1 < nrp[i])
                     nrp[i] = nrp[j] + 1;
       }
}

void Write()
{ 
    ofstream fout(OUT);
    fout << nrp[n-1] << '\n';
    fout.close();
}

