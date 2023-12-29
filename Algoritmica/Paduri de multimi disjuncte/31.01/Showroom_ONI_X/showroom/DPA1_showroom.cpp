#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("showroom.in");
ofstream fout("showroom.out");

struct nod{
char inf[21];
nod *urm;
};
nod *L[1002];
int n, m, a, r, k, f[1002],g[1002];
int nr=9001;

nod *lista(char s[]){
int n,i,j;
nod *q, *vf;
char cuv[21];
n=strlen(s);
i=0;
vf=0;
while(i<n)
 if(s[i]==' ')
  i++;
   else
   {
       j=0;
       while (i<n&&s[i]!=' '){
       cuv[j]=s[i];
       i++;
       j++;
       }
       cuv[j]='\0';
       //inserare cuv in stiva
       q=new nod;
       strcpy(q->inf,cuv);
       q->urm=vf;
       vf=q;
   }
return vf;
}

void cit(){
char s[1002];
int i;
fin>>n>>a>>r>>k;
fin.get();
for(i=1;i<=n;i++){
fin.get(s,1000,'\n');
L[i]=lista(s);
fin.get();
}
fin.close();
}

int exista(char s[], int i){
nod *q;
q=L[i];
while(q){
 if(strcmp(s,q->inf)==0)
  return 1;
 q=q->urm;
}
return 0;
}

void comasare(){
 int i, j, sw, k, w;
 nod *q, *r;
 do{
 w=0;
 for(i=1;i<n;i++)
  for(j=i+1;j<=n;j++)
   {
       q=L[i];sw=0;
       while(q){
        if(exista(q->inf,j))
         {sw=1;}
        r=q;
        q=q->urm;
       }
       if(sw){
        r->urm=L[j];
       for(k=j+1;k<=n;k++)
        L[k-1]=L[k];
       n--;
       j--;
       w=1;
       }
   }
 }while(w);

}

void afis1(nod *q){
while(q){
fout<<q->inf<<"   ";
q=q->urm;
}
fout<<'\n';
}


void afis(){
int i;
for(i=1;i<=n;i++)
 afis1(L[i]);
fout<<'\n';
}

void dist(int i){
nod *p, *q, *r;
p=L[i];
while(p && p->urm){
 q=p->urm;
 r=p;
 while(r && q)
  if(strcmp(q->inf,p->inf)==0){
   r->urm=q->urm;
   delete q;
   q=r->urm;
  }
   else
   {
       r=r->urm;
       q=q->urm;
   }
 p=p->urm;
}
}

void distincte(){
int i;
for(i=1;i<=n;i++)
 dist(i);
}

int nrmodelefirma(int i){
nod *q;
int k=0;
q=L[i];
while (q){
k++;
q=q->urm;
}
return k;
}

void numere(){
int i;
for(i=1;i<=n;i++){
 g[i]=nrmodelefirma(i);
 f[i]=(a+(i-1)*r)%k;
}
}

int comb(int k, int n){
int x[100002], y[100002],i,j;
x[0]=1;
for(i=1;i<=n;i++){
 y[0]=1;y[i]=1;
 for(j=1;j<i;j++)
  y[j]=(x[j-1]+x[j])%nr;
 for(j=0;j<=i;j++)
  x[j]=y[j];
}
return x[k];
}

int numarvariante(){
int p,i;
numere();
p=1;
for(i=1;i<=n;i++){
 if(g[i]>=f[i])
 p=(p*comb(f[i],g[i]))%nr;
 }
return p;
}

void afisOK(){
fout<<n<<'\n';
fout<<numarvariante()<<'\n';
fout.close();
}

int main()
{
    cit();
    //afis();
    comasare();
    //afis();
    distincte();
    //afis();
    afisOK();
    return 0;
}
