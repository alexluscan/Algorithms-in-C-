#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
 #define gc getchar_unlocked
#else
 #define gc getchar
#endif
 
#define MAX 400000
using namespace std;
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
 
int n,q;
 
int tree[MAX];
bool flag[MAX]={0};
 
void update(int i,int start,int end,int qs,int qe)
{
    if(flag[i])
    {
      tree[i] = ((end-start)+1)-tree[i];
      if(start!=end)
      {
         flag[2*i] = (!flag[2*i]);
            flag[2*i+1] = (!flag[2*i+1]);
      }
      flag[i]=0;
    }
 
 
    if(qs>end||qe<start)
    return;
 
    if(qs<=start && qe>=end)
    {
        tree[i] = ((end-start)+1)-tree[i];
        
        if(start!=end)
        {
           flag[2*i] = (!flag[2*i]);
            flag[2*i+1] = (!flag[2*i+1]);
        }
 
        return;
    }
 
    int mid = (start + end)/2;
 
    update(2*i,start,mid,qs,qe);
    update(2*i+1,mid+1,end,qs,qe);
 
    tree[i] = tree[2*i] + tree[2*i+1];
}
 
int query(int i,int start,int end,int qs,int qe)
{
 
    if(qs>end||qe<start)
    return -1;
 
    if(flag[i]) // if the node need to be updated
    {
        tree[i] = end-start+1-tree[i];
        if(start!=end)
        {
            flag[2*i] = (!flag[2*i]);
            flag[2*i+1] = (!flag[2*i+1]);
        }
        flag[i]=0;
    }
 
    if(qs<=start && qe>=end)
    return tree[i];
 
    int mid = (start+end)/2;
 
    int id1 = query(2*i,start,mid,qs,qe);
    int id2 = query(2*i+1,mid+1,end,qs,qe);
 
   
    if(id1==-1)return id2;
    if(id2==-1)return id1;
 
    return id1 + id2;
 
}
 
int main()
{
 
    //scanf("%d%d",&n,&q);
    scanint(n);
    scanint(q);
    int type,a,b;
 
    for(int i=0;i<q;i++)
    {
        //scanf("%d%d%d",&type,&a,&b);
        scanint(type);scanint(a);scanint(b);
 
        if(type==1)
        printf("%d\n",query(1,0,n-1,a,b));
        else
        update(1,0,n-1,a,b);
 
       // cout<<tree[1]<<"\n";
 
    }
 
 
    return 0;
}
  
