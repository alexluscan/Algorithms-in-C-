// Ok infoarena
#include <cstdio>
#include <vector>
#include <queue>
 
FILE* in;
FILE* out;
 
const int Q=200001;
int nrnod,nrarc;
 
struct arc{
    int to;
    int val;
};
 
struct heap_class{
    int from;
    int to;
    int val;
};
 
struct cmp{
    bool operator()(heap_class a, heap_class b)
    {
        return a.val>b.val;
    }
};
 
std::vector<arc> v[Q];
std::priority_queue<heap_class,std::vector<heap_class>,cmp> h;
 
bool viz[Q];
int nrviz=1;
 
int sum,nrrez;
arc rez[Q];
 
void LuiPrim()
{
    for(int i=0; i<v[1].size(); i++)
    {
        h.push(heap_class{1,v[1][i].to,v[1][i].val});
    }
 
    viz[1]=true;
 
    heap_class act;
    int actnod;
 
    while(!h.empty() && nrviz!=nrnod)
    {
        act=h.top();
        h.pop();
        actnod=act.to;
        if(viz[actnod]==1)
            continue;
        viz[actnod]=1;
        nrviz++;
 
        //printf("%d %d %d\n",act.from,act.to,act.val);
        sum+=act.val;
        rez[++nrrez].to=act.from;
        rez[nrrez].val=act.to;
 
        for(int i=0; i<v[actnod].size(); i++)
        {
            if(viz[v[actnod][i].to]==0)
            {
                h.push(heap_class{actnod,v[actnod][i].to,v[actnod][i].val});
            }
        }
    }
}
 
int main()
{
    in=fopen("apm.in","r");
    out=fopen("apm.out","w");
 
    fscanf(in,"%d %d",&nrnod,&nrarc);
 
    int a,b,c;
 
    for(int i=1; i<=nrarc; i++)
    {
        fscanf(in,"%d%d%d",&a,&b,&c);
        v[a].push_back(arc{b,c});
        v[b].push_back(arc{a,c});
    }
 
    LuiPrim();
 
    fprintf(out,"%d\n%d\n",sum,nrnod-1);
 
    for(int i=1; i<nrnod; i++)
        fprintf(out,"%d %d\n",rez[i].to,rez[i].val);
 
    return 0;
}
