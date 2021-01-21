/**Using heavy light decomposition**/
/**Same as Lightoj Aladdin and return journey**/
/**assume node start from 0**/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=3e4+10;
int node,cn=0,arr[mxn],depth[mxn],sbtr[mxn],p[mxn],par[mxn][16],pos[mxn],chainHead[mxn],chainID[mxn],chainNO=0;
int tree[4*mxn];
vector<int>adj[mxn],euler;
void reset()
{
    cn=0;
    chainNO=0;
    memset(chainHead,-1,sizeof chainHead);
    memset(par,-1,sizeof par);
    euler.clear();
    for(int i=0;i<node;i++)
        adj[i].clear();
}
void dfs(int src,int parent,int lev)
{
    depth[src]=lev;
    p[src]=parent;
    sbtr[src]=1;
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent)
        {
            dfs(adj[src][i],src,lev+1);
            sbtr[src]+=sbtr[adj[src][i]];
        }
}
void LCAinit()
{
    for(int i=0;i<node;i++)
        par[i][0]=p[i];
    for(int k=1;k<16;k++)
        for(int i=0;i<node;i++)
            if(par[i][k-1]!=-1)
                par[i][k]=par[par[i][k-1]][k-1];
}
void hld(int src,int parent)
{
    if(chainHead[chainNO]==-1)
        chainHead[chainNO]=src;
    chainID[src]=chainNO;
    euler.push_back(src);
    pos[src]=cn++;
    int mx=-1,idx=-1;
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=parent && mx<=sbtr[adj[src][i]])
        {
            mx=sbtr[adj[src][i]];
            idx=i;
        }
    if(idx!=-1)
        hld(adj[src][idx],src);
    for(int i=0;i<adj[src].size();i++)
        if(i!=idx && adj[src][i]!=parent)
        {
            chainNO++;
            hld(adj[src][i],src);
        }
}
int LCAquery(int u,int v)
{
    if(depth[u]>depth[v])
        swap(u,v);
    for(int i=15;i>=0;i--)
        if(depth[v]-(1<<i)>=depth[u])
            v=par[v][i];
    if(u==v)
        return u;
    for(int i=15;i>=0;i--)
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
            u=par[u][i],v=par[v][i];
    return p[u];
}
void build(int left,int right,int idx)
{
    if(left==right)
    {
        tree[idx]=arr[euler[left]];
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    tree[idx]=tree[idx*2+1]+tree[idx*2+2];
}
void update(int left,int right,int idx,int qidx,int val)
{
    if(qidx<left || qidx>right)
        return ;
    if(left==right)
    {
        tree[idx]=val;
        return ;
    }
    int mid=(left+right)/2;
    update(left,mid,idx*2+1,qidx,val);
    update(mid+1,right,idx*2+2,qidx,val);
    tree[idx]=tree[idx*2+1]+tree[idx*2+2];
}
ll query(int left,int right,int idx,int ql,int qr)
{
    if(ql>right || qr<left)
        return 0;
    if(ql<=left && qr>=right)
        return tree[idx];
    int mid=(left+right)/2;
    ll p,q;
    p=query(left,mid,idx*2+1,ql,qr);
    q=query(mid+1,right,idx*2+2,ql,qr);
    return p+q;
}
ll hld_query(int u,int v)
{
    int lchain,rchain=chainID[v];
    ll ans=0;
    while(1)
    {
        lchain=chainID[u];
        if(lchain==rchain)
        {
            ans+=query(0,euler.size()-1,0,pos[v],pos[u]);
            break;
        }
        ans+=query(0,euler.size()-1,0,pos[chainHead[lchain]],pos[u]);
        u=chainHead[lchain];
        u=par[u][0];
    }
    return ans;
}
int main()
{
    int t,_case=0;
    scanf("%d",&t);
    while(t--)
    {
        reset();
        scanf("%d",&node);
        for(int i=0;i<node;i++)
            scanf("%d",arr+i);
        for(int i=0;i<node-1;i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0,0,0);
        LCAinit();
        hld(0,0);
        build(0,euler.size()-1,0);
        int q;
        scanf("%d",&q);
        printf("Case %d:\n",++_case);
        while(q--)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            if(x==0)
            {
                int lca=LCAquery(y,z);
                ll res=hld_query(y,lca);
                res+=hld_query(z,lca);
                printf("%lld\n",res-arr[lca]);
            }
            else  
            {
                arr[y]=z;
                y=pos[y];
                update(0,euler.size()-1,0,y,z);
            }
        }
    }
    return 0;
}
