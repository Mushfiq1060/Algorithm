#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int node,depth[mxn],p[mxn],par[mxn][18];
vector<int>tree[mxn];
void dfs(int src,int parent,int lev)
{
    depth[src]=lev;
    p[src]=parent;
    for(int i=0;i<tree[src].size();i++)
        if(tree[src][i]!=parent)
            dfs(tree[src][i],src,lev+1);
}
void LCAinit()
{
    memset(par,-1,sizeof par);
    for(int i=1;i<=node;i++)
        par[i][0]=p[i];
    for(int k=1;k<=17;k++)  
        for(int i=1;i<=node;i++)
            if(par[i][k-1]!=-1)
                par[i][k]=par[par[i][k-1]][k-1];
}
int LCAquery(int u,int v)
{
    if(depth[v]<depth[u])
        swap(u,v);
    for(int i=17;i>=0;i--)
        if(depth[v]-(1<<i)>=depth[u])
            v=par[v][i];
    if(u==v)
        return u;
    for(int i=17;i>=0;i--)
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
            u=par[u][i],v=par[v][i];
    return p[u];
}
int main()
{
    scanf("%d",&node);
    for(int i=0;i<node-1;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1,0,0);
    LCAinit();
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        int res=LCAquery(u,v);
        printf("%d\n",res);
    }
    return 0;   
}