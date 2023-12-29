//Emanuela Cerchez 40 puncte
#include <fstream.h>
#include <string.h>
#define InFile  "text.in"
#define OutFile "text.out"
#define abs(x) ((x)>0?(x):(-(x)))
#define LgMax 202
#define R 1000003
#define Inf 2000000000

char s[LgMax], v[]="aeiouy";
int n, lg;
int poz[LgMax];
//poz[i]=pozitia celei mai apropiate vocale >=i
int sol[LgMax], solmin[LgMax];
long int nr;
long int costmin, cost;


void citire ();
void rezolva (int);
void afisare ();
void det_poz();

int main ()
{
int i, j, k;
ofstream fout (OutFile);
citire ();
det_poz();
costmin=Inf;
rezolva(1);
fout<<nr<<'\n';
fout<<costmin<<'\n';

for (i=0, k=1; k<n; k++)
    { for (j=i; j<solmin[k]; j++) fout<<s[j];
      i=solmin[k];
      fout<<' ';
    }
for (j=solmin[n-1]; j<lg; j++) fout<<s[j];
fout<<'\n';
fout.close ();
return 0;
}

void citire ()
{
 ifstream fin (InFile);
 fin.getline(s, LgMax);
 lg=strlen(s);
 fin>>n;
 fin.close ();
}

void det_poz()
{
int i, last=-1;
for (i=lg-1; i>=0; i--)
    {if (strchr(v,s[i]))last=i;
     poz[i]=last;}
}


void rezolva (int k)
//pozitia la care incepe cel de-al k-lea cuvant
{
int t;
if (k==n)
   {
    if (lg-sol[n-1]<=20)
       {
        //am determinat o solutie
        nr=(nr+1)%R;
        if (cost+(lg-sol[k-1])*(lg-sol[k-1])<costmin)
           {
           costmin=cost+(lg-sol[k-1])*(lg-sol[k-1]);
           for (t=1; t<n; t++) solmin[t]=sol[t];
           }
        }
   }
   else
   for (t=1; t<=20 && sol[k-1]+t<lg; t++)
       if (poz[sol[k-1]] <sol[k-1]+t && //exista o vocala in cuvantul precedent
           poz[sol[k-1]+t]!=-1 )        //mai exista vocale in continuare
           {
           sol[k]=sol[k-1]+t;
           cost+=t*t;
           rezolva(k+1);
           cost-=t*t;
           }
}