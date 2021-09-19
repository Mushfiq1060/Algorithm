#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
set<int>adj[mxn];
int sbtr[mxn],p[mxn];
int dfs(int src,int par)
{
  sbtr[src]=1;
  for(auto it=adj[src].begin();it!=adj[src].end();it++)
    if(*it!=par)
      sbtr[src]+=dfs(*it,src);
  return sbtr[src];
}
int find_centroid(int src,int par,int sz)
{ 
  for(auto it=adj[src].begin();it!=adj[src].end();it++)
    if(*it!=par && sbtr[*it]>sz/2)
      return find_centroid(*it,src,sz);
  return src;
}
void centroid_decompose(int src,int par)
{
  int sbtr_size=dfs(src,par);
  int centroid=find_centroid(src,par,sbtr_size);
  p[centroid]=par;
  for(auto it=adj[centroid].begin();it!=adj[centroid].end();it++)
  {
    adj[*it].erase(centroid);
    centroid_decompose(*it,centroid);
  }
}
int main()
{
  int node;
  cin>>node;
  for(int i=0;i<node-1;i++)
  {
    int u,v;
    cin>>u>>v;
    adj[u].insert(v);
    adj[v].insert(u);
  }
  centroid_decompose(1,-1);
  for(int i=1;i<=node;i++)
    cout<<i<<" -> "<<p[i]<<endl; /// we can now build decompose tree based on parent of node i
  return 0;
}
