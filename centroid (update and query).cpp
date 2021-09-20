/** https://codeforces.com/contest/342/problem/E  **/


#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=2e5+10;
vector<int>tree[mxn];
set<int>adj[mxn];
int node,q,sbtr[mxn],depth[mxn],p[mxn],cp[mxn],par[mxn][20],dist[mxn];
void dfs(int src,int parent,int lev)
{
  depth[src]=lev;
  p[src]=parent;
  for(int i=0;i<tree[src].size();i++)
    if(tree[src][i]!=parent)
      dfs(tree[src][i],src,lev+1);
}
int dfs1(int src,int parent)
{
  sbtr[src]=1;
  for(auto it=adj[src].begin();it!=adj[src].end();it++)
    if(*it!=parent)
      sbtr[src]+=dfs1(*it,src);
  return sbtr[src];
}
int find_centroid(int src,int parent,int sz)
{
  for(auto it=adj[src].begin();it!=adj[src].end();it++)
    if(*it!=parent && (sbtr[*it]*2)>sz)
      return find_centroid(*it,src,sz);
  return src;
}
void centroid_decompose(int src,int parent)
{
  int sbtr_size=dfs1(src,parent);
  int centroid=find_centroid(src,parent,sbtr_size);
  cp[centroid]=parent;
  for(auto it=adj[centroid].begin();it!=adj[centroid].end();it++)
  {
    adj[*it].erase(centroid);
    centroid_decompose(*it,centroid);
  }
}
void LCAinit()
{
  memset(par,-1,sizeof par);
  for(int i=1;i<=node;i++)
    par[i][0]=p[i];
  for(int k=1;k<=19;k++)  
    for(int i=1;i<=node;i++)
      if(par[i][k-1]!=-1)
        par[i][k]=par[par[i][k-1]][k-1];
}
int LCAquery(int u,int v)
{
  if(depth[v]<depth[u])
    swap(u,v);
  for(int i=19;i>=0;i--)
    if(depth[v]-(1<<i)>=depth[u])
      v=par[v][i];
  if(u==v)
    return u;
  for(int i=19;i>=0;i--)
    if(par[u][i]!=-1 && par[u][i]!=par[v][i])
      u=par[u][i],v=par[v][i];
  return p[u];
}
int func(int u,int v)
{
  int lca=LCAquery(u,v);
  return depth[u]+depth[v]-2*depth[lca];
}
void update(int x)
{
  int cur=x;
  while(x!=-1)
  {
    dist[x]=min(dist[x],func(cur,x));
    x=cp[x];
  }
}
int query(int x)
{
  int ans=1e8,cur=x;
  while(x!=-1)
  {
    ans=min(ans,dist[x]+func(cur,x));
    x=cp[x];
  }
  return ans;
}
int main()
{
  scanf("%d%d",&node,&q);
  for(int i=0;i<node-1;i++)
  {
    int u,v;
    scanf("%d%d",&u,&v);
    tree[u].push_back(v);
    tree[v].push_back(u);
    adj[u].insert(v);
    adj[v].insert(u);
  }
  dfs(1,-1,0);
  LCAinit();
  centroid_decompose(1,-1);
  for(int i=1;i<=node;i++)
    dist[i]=1e7;
  update(1);
  while(q--)
  {
    int t,x;
    scanf("%d%d",&t,&x);
    if(t==1)
      update(x);
    else  
      printf("%d\n",query(x));
  }
  return 0;
}
