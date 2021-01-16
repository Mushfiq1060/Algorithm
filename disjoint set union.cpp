#include<bits/stdc++.h>
using namespace std;
int parent[100],_rank[100];
class dsu
{
public:
    void makeset(int n)
    {
        for(int i=1;i<=n;i++)
            parent[i]=i,_rank[i]=0;
    }
    int _find(int x)
    {
        if(parent[x]!=x)
            parent[x]=_find(parent[x]);
        return parent[x];
    }
    void _union(int u,int v)
    {
        int x=_find(u),y=_find(v);
        if(x==y)
            return;
        else if(_rank[x]>=_rank[y])
            parent[y]=x,_rank[x]+=_rank[y]+1;
        else if(_rank[x]<_rank[y])
            parent[x]=y,_rank[y]+=_rank[x]+1;
    }
};
int main()
{
    dsu ds;
    int node,edge,u,v;
    cin>>node>>edge;
    ds.makeset(node);
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        ds._union(u,v);
    }
    cout<<"_______________________"<<endl;
    for(int i=1;i<=node;i++)
        cout<<i<<" "<<parent[i]<<endl;
    return 0;
}
