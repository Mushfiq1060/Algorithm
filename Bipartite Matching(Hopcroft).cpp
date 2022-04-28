/*
  Bipartite Matching(Hopcroft Karp algorithm)
  Time Complexity: O (|E|√|V|)
*/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int inf=1e9+7;
namespace HopcroftKarp
{
  int n;
  vector<vector<int>>g;
  vector<int>dist,match;
  void initialize(int _n,int _m)
  {
    n=_n;
    int sz=_n+_m+1;
    g=vector<vector<int>>(sz);
    dist=vector<int>(sz,0);
    match=vector<int>(sz,0);
  }
  void addEdge(int u,int v)
  {
    g[u].push_back(v+n); // set2 is mapped with (value(v)+set1 size(n))
  }
  bool BFS()
  {
    queue<int>qu;
    for(int i=1;i<=n;i++){
      if(!match[i]){
        dist[i]=0;
        qu.push(i);
      }
      else{
        dist[i]=inf;
      }
    }
    dist[0]=inf;
    while(!qu.empty()){
      int u=qu.front();
      qu.pop();
      for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(dist[match[v]]==inf){
          dist[match[v]]=dist[u]+1;
          qu.push(match[v]);
        }
      }
    }
    return dist[0]!=inf;
  }
  bool dfs(int src)
  {
    if(!src){
      return true;
    }
    for(int i=0;i<g[src].size();i++){
      int u=g[src][i];
      if(dist[match[u]]==dist[src]+1 && dfs(match[u])){
        match[src]=u;
        match[u]=src;
        return true;
      }
    }
    dist[src]=inf;
    return false;
  }
  int maximumMatching()
  {
    int ans=0;
    while(BFS()){
      for(int i=1;i<=n;i++){
        if(!match[i] && dfs(i)){
          ans++;
        }
      }
    }
    return ans;
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin>>t;
  while(t--){
    int n,m;
    cin>>n>>m;
    HopcroftKarp::initialize(n,m);
    for(int i=0;i<m;i++){
      int u,v;
      cin>>u>>v;
      HopcroftKarp::addEdge(u,v);
    }
    cout<<HopcroftKarp::maximumMatching()<<endl;
  }
  return 0;
}
