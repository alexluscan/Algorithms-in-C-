// CodeChef September Long Challenge. Problem MLCHEF
// Tester's solution. Written by Sergey Kulik

#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define inf 2000000000
#define maxn 111111

int fw[maxn],inv[maxn],L,R,m,qt,x,tin[maxn],tout[maxn],timer,f[maxn],p[maxn],hp[maxn],n,i,pi;

struct node{
	int l,r;
	long long mi,add;
}tree[maxn*4];

void dfs(int k){ // DFS. gets input and output times for every node. quite standard thing
	tin[k]=++timer; // in time
	int q=f[k];
	while(q){
		dfs(q); // explore the sons
		q=p[q];
	}
	tout[k]=timer; // out time
}

void init(int pos,int l,int r){ // standard segment tree initialization
	tree[pos].l=l,tree[pos].r=r; // vertex pos corresponds to the interval [l; r]
	if(l<r){ // if there are sons
		init(pos+pos,l,(l+r)/2); // left son
		init(pos+pos+1,(l+r)/2+1,r); // right son
		tree[pos].mi=min(tree[pos+pos].mi,tree[pos+pos+1].mi); // get the minimum in the subtree
	}else tree[pos].mi=hp[inv[l]]; // otherwise, minimum is clear
}

void modify(int pos,int l,int r,int x){ // standard segment tree modification
	if(tree[pos].l==l&&tree[pos].r==r)tree[pos].add-=x;else{ // if the whole interval is covered
		if(l<=min(r,tree[pos+pos].r))modify(pos+pos,l,min(r,tree[pos+pos].r),x); // modify the left son, if we have to
		if(max(l,tree[pos+pos+1].l)<=r)modify(pos+pos+1,max(l,tree[pos+pos+1].l),r,x); // modify the right son, if we have to
		tree[pos].mi=min(tree[pos+pos].mi+tree[pos+pos].add,tree[pos+pos+1].mi+tree[pos+pos+1].add); // recalculate minimum in the subtree
	}
}

void fwt_modify(int j){ // standard function for modification on the fenwick tree
	for(;j<maxn;j=(j|(j-1))+1)++fw[j];
}

void seek(int pos){ // gets some chef with zero or less health and replaces him to the infinite-health chef
	if(tree[pos].l==tree[pos].r){ // if there are no choices
		tree[pos].add+=inf; // infinite health
		fwt_modify(tree[pos].l); // mark the chef as dead
		return ;
	}
	if(tree[pos+pos].mi+tree[pos+pos].add<tree[pos+pos+1].mi+tree[pos+pos+1].add)seek(pos+pos);else seek(pos+pos+1); // get the minimal one
	tree[pos].mi=min(tree[pos+pos].mi+tree[pos+pos].add,tree[pos+pos+1].mi+tree[pos+pos+1].add); // recalculate the minimum subtree
}

int fwt_query(int j){ // standard function for query on the fenwick tree
	int rt=0;
	for(;j;j=(j&(j-1)))rt+=fw[j];
	return rt;
}

int main (int argc, char * const argv[]) {
	scanf("%d",&n); // get N
	assert(1<=n&&n<=100000); // input validation
	for(i=1;i<=n;i++){
		scanf("%d%d",&hp[i],&pi); // read the health and the superior of the i-th chef
		assert(1<=hp[i]&&hp[i]<=1000000000); // input validation
		assert(pi<i); // input validation
		p[i]=f[pi];f[pi]=i; // add an edge
	}
	dfs(0); // get in and out times
	for(i=1;i<=n;i++)inv[tin[i]]=i;
	init(1,1,timer); // init the segment tree
	while(tree[1].mi+tree[1].add<1)seek(1);	// erase the chefs with zero health already
	scanf("%d",&m); // get the number of queries
	assert(1<=m&&m<=100000); // input validation
	for(i=1;i<=m;i++){
		scanf("%d%d",&qt,&x); // get the query
		assert(qt==1||qt==2); // input validation
		assert(0<=x&&x<=n); // input validation
		L=tin[x]+1; // get in time for the subtree
		R=tout[x]; // get out time for the subtree
		if(qt==2){
			if(L>R)puts("0");else printf("%d\n",(R-L+1)-(fwt_query(R)-fwt_query(L-1))); // get the answer to the 2-type query
		}else{
			scanf("%d",&x);
			assert(1<=x&&x<=10000); // input validation
			if(L<=R)modify(1,L,R,x); // decrease the values in the range [L; R]
			while(tree[1].mi+tree[1].add<1)seek(1); // erase the chefs with zero or less health
		}
	}
    return 0;
}
