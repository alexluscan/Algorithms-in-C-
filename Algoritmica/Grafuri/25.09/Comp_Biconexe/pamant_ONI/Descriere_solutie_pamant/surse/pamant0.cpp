// prof. Carmen Popescu 

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

#define MAX 200000
ifstream f("pamant.in");
ofstream g("pamant.out");

int nr,n,m,d[MAX],v[MAX],start,nrfii,nc=0,nrp=0,k,mn;
set<int> s[MAX];	// listele de adiacenta
set<int> art;		// multimea punctelor de articulatie
set<int> comp;		// codurile proprietatilor

void VIZ(int i,int tata)
{
	set<int>::iterator it;
	int j;
	if (i<mn)
		mn=i;
	d[i]=++nr;
	v[i]=nr;
	for (it=s[i].begin();it!=s[i].end();it++) {
		j=*it;
		if (d[j]==0) {		// j este "atins" pentru prima data
			if (i==start)
				nrfii++;
			VIZ(j,i);
			if (v[j]>=d[i]) {  // i e punct de articulatie
				if (tata!=-1)
					art.insert(i);
			}
			if (v[j]<v[i])
				v[i]=v[j];
		}
		else
			if (j!=tata)
				if (v[j]<v[i])		// (i,j) = muchie de intoarcere
					v[i]=v[j];
	}
}

void citire()
{
	int x,y;
	f>>n>>m;
	for (int i=0;i<m;i++) {
		f>>x>>y;
		s[x].insert(y);
		s[y].insert(x);
	}
}


int main()
{
	int i;
	set<int>::iterator it;
	set<int>::iterator it1;
	citire();

	// pentru fiecare componenta conexa se cauta punctele de articulatie
	nr=k=0;
	for (i=1;i<=n;i++) {
		mn=n+1;
		if (d[i]==0) {
			start=i;
			nrfii=0;
			VIZ(start,-1);

			// radacina are cel putin 2 fii => pct de articulatie
			if (nrfii>1) {
				art.insert(start);
			}

			k++;
			comp.insert(mn);
		}
	}
	g<<k<<"\n";
	for (it=comp.begin();it!=comp.end();it++)
		g<<*it<<" ";
	g<<"\n";

	// numarul de puncte de articulatie
	g<<art.size()<<"\n";

	// afisarea punctelor de articulatie
	for (it=art.begin();it!=art.end();it++)
		g<<*it<<" ";
	g<<"\n";

}
