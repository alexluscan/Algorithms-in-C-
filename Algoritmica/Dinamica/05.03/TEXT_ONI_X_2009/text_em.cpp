//Emanuela Cerchez - 100 puncte
#include <fstream.h>
#include <string.h>
#define InFile  "text.in"
#define OutFile "text.out"
#define abs(x) ((x)>0?(x):(-(x)))
#define LgMax 210
#define Inf 2000000000
#define R 1000003

char s[LgMax], v[]="aeiouy";
int n, lg, cine;
int poz[LgMax];
//poz[i]=pozitia celei mai apropiate vocale >=i

long int nr[LgMax][2];
//nr[i][k]=numarul de posibilitati de a construi k cuvinte incepand cu pozitia i

long int cost[LgMax][2];
unsigned char urm[LgMax][LgMax];

void citire ();
void rezolvare ();
void afisare ();
void det_poz();
void numarare();
void armonie();

int main ()
{
int i, j, k;
ofstream fout (OutFile);
citire ();
det_poz();
numarare ();

fout<<nr[0][cine]<<'\n';

armonie();
fout<<cost[0][cine]<<'\n';

for (i=0, k=n; k>0; k--)
    { for (j=i; j<urm[i][k]; j++) fout<<s[j];
       i=urm[i][k];
       if (k>1) fout<<' ';
      }
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

void numarare ()
{
int i, k, t, ok;
long int sum;
cine=0;
for (i=0; i<lg; i++)
    if (poz[i]!=-1 && lg-i<=20) nr[i][0]=1;
       else
       nr[i][0]=-1;

for (k=2; k<=n; k++)
    {
    cine=1-cine;
    for (i=lg-1; i>=0; i--)
        {
        nr[i][cine]=-1;
        sum=0; ok=0;
        for (t=1; t<=20 && i+t-1<lg; t++)
            {if (poz[i]==-1 || i+t-1 <poz[i]) continue;
             if (nr[i+t][1-cine]!=-1)
                {ok=1; sum=(sum+nr[i+t][1-cine])%R;}
            }
        if (ok) nr[i][cine]=sum;
        }
    }
}


void armonie ()
{
int i, k, t, tmin;
long int min;

cine=0;
for (i=0; i<lg; i++)
    {
    if (poz[i]!=-1 && lg-i<=20) {cost[i][0]=(lg-i)*(lg-i); urm[i][1]=lg;}
       else
       {cost[i][0]=Inf; urm[i][1]=0;}
    }
for (i=0; i<=lg; i++) urm[lg][i]=0;
cost[lg][0]=cost[lg][1]=Inf;

for (k=2; k<=n; k++)
    {
    cine=1-cine;
    for (i=lg-1; i>=0; i--)
        {
        cost[i][cine]=Inf; urm[i][k]=0;
        min=Inf; tmin=-1;

        for (t=1; t<=20 && i+t-1<lg; t++)
            {if (poz[i]==-1 || i+t-1 <poz[i]) continue;
             if (cost[i+t][1-cine]==Inf) continue;

             if (cost[i+t][1-cine]+t*t<min)
                {
                 min=cost[i+t][1-cine]+t*t;
                 tmin=t;
                }
            }
        if (tmin!=-1) {cost[i][cine]=min; urm[i][k]=i+tmin;}
        }

    }

}
