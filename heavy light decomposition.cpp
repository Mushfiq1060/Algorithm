/**It is used in tree when there is update and query in tree**/
/**  https://cses.fi/problemset/task/2134/ **/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=2e5+10;
int n,q,arr[mxn],sbtr[mxn],cn=0,pos[mxn],chainHead[mxn],chainID[mxn],depth[mxn],par[mxn][19],p[mxn],chainNO=0;
vector<int>adj[mxn],euler[mxn],tree[mxn];
void dfs(int src,int parent,int lev)
{
    sbtr[src]=1;
    p[src]=parent;
    depth[src]=lev;
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent) 
        {
            dfs(adj[src][i],src,lev+1);
            sbtr[src]+=sbtr[adj[src][i]];
        }
}
void hld(int src,int parent)
{
    if(chainHead[chainNO]==-1)
        chainHead[chainNO]=src;
    chainID[src]=chainNO;
    euler[chainNO].push_back(src);
    pos[src]=cn++;
    int mx=-1,idx=-1;
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent && sbtr[adj[src][i]]>=mx)
        {
            mx=sbtr[adj[src][i]];
            idx=i;
        }
    if(idx!=-1)
        hld(adj[src][idx],src);
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent && i!=idx)
        {
            chainNO++;
            cn=0;
            hld(adj[src][i],src);
        }
}
void LCAinit()
{   
    memset(par,-1,sizeof par);
    for(int i=0;i<=n;i++)
        par[i][0]=p[i];
    for(int k=1;k<19;k++)
        for(int i=1;i<=n;i++)
            if(par[i][k-1]!=-1)
                par[i][k]=par[par[i][k-1]][k-1];
}
void build(int left,int right,int idx,int seg)
{
    if(left==right)
    {
        tree[seg][idx]=arr[euler[seg][left]];
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1,seg);
    build(mid+1,right,idx*2+2,seg);
    tree[seg][idx]=max(tree[seg][idx*2+1],tree[seg][idx*2+2]);
}
void update(int left,int right,int idx,int qidx,int val,int seg)
{
    if(qidx<left || qidx>right)
        return ;
    if(left==right)
    {
        tree[seg][idx]=val;
        return ;
    }
    int mid=(left+right)/2;
    update(left,mid,idx*2+1,qidx,val,seg);
    update(mid+1,right,idx*2+2,qidx,val,seg);
    tree[seg][idx]=max(tree[seg][idx*2+1],tree[seg][idx*2+2]);
}
int LCAquery(int u,int v)
{
    if(depth[u]>depth[v])
        swap(u,v);
    int lg=log2(depth[v]);
    for(int i=lg;i>=0;i--)
        if(depth[v]-(1<<i)>=depth[u])
            v=par[v][i];
    if(u==v)
        return u;
    for(int i=lg;i>=0;i--)
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
            u=par[u][i],v=par[v][i];
    return p[u];
}
int query(int left,int right,int idx,int ql,int qr,int seg)
{
    if(ql>right || qr<left)
        return INT_MIN;
    if(ql<=left && qr>=right)
        return tree[seg][idx];
    int mid=(left+right)/2,p,q;
    p=query(left,mid,idx*2+1,ql,qr,seg);
    q=query(mid+1,right,idx*2+2,ql,qr,seg);
    return max(p,q);
}
int hldquery(int u,int lca)
{
    int uchain,vchain=chainID[lca],res=-1;
    while(1)
    {
        uchain=chainID[u];
        if(uchain==vchain)
        {   
            res=max(res,query(0,euler[uchain].size()-1,0,pos[lca],pos[u],uchain));
            break;
        }
        res=max(res,query(0,euler[uchain].size()-1,0,pos[chainHead[uchain]],pos[u],uchain));
        u=chainHead[uchain];
        u=p[u];
    }
    return res;
}
int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",arr+i);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,0);
    memset(chainHead,-1,sizeof chainHead);
    hld(1,0);
    LCAinit();
    for(int i=0;i<=chainNO;i++)
    {
        tree[i].resize(4*euler[i].size()+5);
        build(0,euler[i].size()-1,0,i);
    }
    while(q--)
    {
        int t,u,x;
        scanf("%d %d %d",&t,&u,&x);
        if(t==1)
        {
            int id=chainID[u];
            update(0,euler[id].size()-1,0,pos[u],x,id);
        }
        else 
        {
            int lca=LCAquery(u,x);
            int res=hldquery(u,lca);
            res=max(res,hldquery(x,lca));
            printf("%d ",res);
        }
    }
    return 0;
}
