/*Codeforces GYM 100962F*/
/*blog - https://codeforces.com/blog/entry/43230*/


#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int freq[mxn],mex=0,len,n,q,cn=0,arr[mxn],in[mxn],out[mxn],depth[mxn],p[mxn],par[mxn][18];
bool vis[mxn];
vector<int>adj[mxn],weight[mxn],euler;
struct info
{
    int l,r,idx,type,lca;
}query[mxn];
void dfs(int src,int parent,int lev)
{
    p[src]=parent;
    depth[src]=lev;
    in[src]=cn++;
    euler.push_back(src);
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent)
        {
            arr[adj[src][i]]=weight[src][i];
            dfs(adj[src][i],src,lev+1);
        }
    out[src]=cn++;
    euler.push_back(src);
}
void LCAinit()
{
    memset(par,-1,sizeof par);
    for(int i=1;i<=n;i++)
        par[i][0]=p[i];
    for(int k=1;k<=17;k++)  
        for(int i=1;i<=n;i++)
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
bool cmp(info a,info b)
{
    int block_own=a.l/len,block_other=b.l/len;
    if(block_own==block_other)
        return a.r<b.r;
    return block_own<block_other;
}
inline void check(int idx)
{
    int node=euler[idx],val=arr[node];
    if(val>n)
        return ;
    if(vis[node])
    {
        freq[val]--;
        if(freq[val]==0)
            mex=min(mex,val);
    }
    else 
    {
        freq[val]++;
        while(freq[mex])
            mex++;
    }
    vis[node]^=1;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        adj[u].push_back(v);
        adj[v].push_back(u);
        weight[u].push_back(w);
        weight[v].push_back(w);
    }
    arr[1]=mxn;
    dfs(1,0,0);
    LCAinit();
    len=sqrt(euler.size());
    for(int i=0;i<q;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(in[u]>in[v])
            swap(u,v);
        int p=LCAquery(u,v);
        if(p==u || p==v)
            query[i]={in[u],in[v],i,0,p};
        else 
            query[i]={out[u],in[v],i,1,p};
    }
    sort(query,query+q,cmp);
    int left=0,right=-1,ans[q];
    for(int i=0;i<q;i++)
    {
        while(right<query[i].r)
            check(++right);
        while(right>query[i].r)
            check(right--);
        while(left<query[i].l)
            check(left++);
        while(left>query[i].l)
            check(--left);
        if(query[i].type==0)
            check(in[query[i].lca]);
        ans[query[i].idx]=mex;
        if(query[i].type==0)
            check(in[query[i].lca]);
    }
    for(int i=0;i<q;i++)
        printf("%d\n",ans[i]);
    return 0;
}
