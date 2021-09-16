/*
    An edge in an undirected connected graph is a bridge if removing it disconnects the graph or increase the
    number of components.
*/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
vector<int>adj[mxn];
bool vis[mxn];
int in[mxn],low[mxn],cn=0;
vector<pair<int,int>>bridge;
void dfs(int src,int par)
{
  vis[src]=1;
  in[src]=low[src]=cn++;
  for(int i=0;i<adj[src].size();i++)
  {
    int u=adj[src][i];
    if(u!=par)
    {
      if(vis[u])  /// (src to u) edge is a back edge
        low[src]=min(low[src],in[u]);
      else  /// (src to u) edge is a forward edge
      {
        dfs(u,src);
        if(low[u]>low[src])
          bridge.push_back({src,u});
        low[src]=min(low[src],low[u]);
      }
    }
  }
}
int main()
{
  int node,edge;
  cin>>node>>edge;
  for(int i=0;i<edge;i++)
  {
    int u,v;
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1,-1);
  cout<<"Bridge edges are : "<<endl;
  for(int i=0;i<bridge.size();i++)
    cout<<bridge[i].first<<" "<<bridge[i].second<<endl;
  return 0;
}
