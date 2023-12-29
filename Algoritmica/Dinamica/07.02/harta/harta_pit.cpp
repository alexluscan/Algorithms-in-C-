/* 100 puncte
  prof. Ionel-Vasile Pit-Rada
*/
#include<fstream>
using namespace std;

 ifstream fin("harta.in");
ofstream fout("harta.out");

int p,n,m,k;
int lung,lat,lx;
int patrate[52],lmax;
char a[1502][1502];
int i1,j1,i2,j2,i;
int l1,c1;
int S,C;

int main(){
    fin>>p>>n>>m>>k;
    if(p==1){
        for(i=1;i<=k;i++){
            fin>>i1>>j1>>i2>>j2;
            lat=i2-i1+1;
            lung=j2-j1+1;
            lx=lat;
            if(lung>lx)lx=lung;
            patrate[lx]++;
            if(lat==lung){
                if(lat>lmax){
                    lmax=lat;
                }
            }
        }
        S=lmax*lmax;
        C=0;
        for(i=1;i<=lmax-2;i++){
            C=C+patrate[i];
        }
        fout<<S<<" "<<C;
    }
    else{
        for(i=1;i<=k;i++){
            fin>>i1>>j1>>i2>>j2;
            for(l1=i1;l1<=i2;l1++){
                a[l1][j1]=1;
                a[l1][j2]=1;
                a[l1][0]=1;//marcat linie care ramane
            }
            for(c1=j1;c1<=j2;c1++){
                a[i1][c1]=1;
                a[i2][c1]=1;
                a[0][c1]=1;//marcat coloana care ramane
            }
        }
        for(l1=1;l1<=n-1;l1++){
            if(a[l1][0]==0 && a[l1+1][0]==0){
                a[l1][0]=2;//linia l1 se va sterge
            }
        }
        for(c1=1;c1<=m-1;c1++){
            if(a[0][c1]==0 && a[0][c1+1]==0){
                a[0][c1]=2;//coloana c1 se va sterge
            }
        }
        //vom pastra doar liniile si coloanele marcate diferit de 2
        for (l1=1;l1<=n;l1++){
            if(a[l1][0]!=2){
                for(c1=1;c1<=m;c1++){
                    if(a[0][c1]!=2){
                        fout<<(int)a[l1][c1]<<" ";
                    }
                }
                fout<<"\n";
            }
        }
    }
    fout.close();
    fin.close();
    return 0;
}
