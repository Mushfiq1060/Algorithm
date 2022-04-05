/*
  Maximum Flow(Edmonds Karp)
  Time Complexity: O(V*E^2)
  Memory: O(v^2)
*/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int inf=1e9+7;
namespace EdmondsKarp
{
  int n;
  vector<vector<int>>g;
  vector<vector<int>>cap;
  void initialize(int sz)
  {
    n=sz;
    g=vector<vector<int>>(n);
    cap=vector<vector<int>>(n,vector<int>(n));
  }
  void addEdge(int u,int v,int w)
  {
    g[u].push_back(v);
    g[v].push_back(u);
    cap[u][v]+=w;
    // cap[v][u]+=w; /// if graph is undirected then use this line
  }
  int BFS(int s,int t)
  {
    int ans=-1;
    vector<int>par(n+5,-1);
    par[s]=-2;
    queue<pair<int,int>>qu;
    qu.push({s,inf});
    while(!qu.empty()){
      int u=qu.front().first,flow=qu.front().second;
      qu.pop();
      for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(par[v]==-1 && cap[u][v]>0){
          par[v]=u;
          int newFlow=min(flow,cap[u][v]);
          if(v==t){
            ans=newFlow;
            break;
          }
          qu.push({v,newFlow});
        }
      }
    }
    if(ans==-1){
      return 0;
    }
    int cur=t;
    while(cur!=s){
      int prev=par[cur];
      cap[prev][cur]-=ans;
      cap[cur][prev]+=ans;
      cur=prev;
    }
    return ans;
  }
  int maxFlow(int s,int t)
  {
    int flow=0,newFlow;
    while(newFlow=BFS(s,t)){
      flow+=newFlow;
    }
    return flow;
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int _t,_case=0;
  cin>>_t;
  while(_t--){
    int n,s,t,c;
    cin>>n>>s>>t>>c; /// n=number of node,s=source,t=sink,c=number of edge
    EdmondsKarp::initialize(n+5);
    for(int i=0;i<c;i++){
      int u,v,w;
      cin>>u>>v>>w;
      EdmondsKarp::addEdge(u,v,w);
    }
    cout<<"Case "<<++_case<<": "<<EdmondsKarp::maxFlow(s,t)<<endl;
  }
  return 0;
}
