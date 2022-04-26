#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=110;
vector<int>g[mxn];
int Right[mxn],Left[mxn];
bool vis[mxn];
bool kuhn(int u)
{
  for(int i=0;i<g[u].size();i++){
    int v=g[u][i];
    if(vis[v]){
      continue;
    }
    vis[v]=1;
    if(Right[v]==-1 || kuhn(Right[v])){
      Right[v]=u;
      Left[u]=v;
      return true;
    }
  }
  return false;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t,_case=0;
  cin>>t;
  while(t--){
    int n,m;
    cin>>n>>m;// n = set 1 number of node, m = edge
    for(int i=0;i<m;i++){
      int u,v;
      cin>>u>>v; // u is set 1 node & v is set 2 node
      g[u].push_back(v);
    }
    int res=0;
    memset(Right,-1,sizeof Right);
    for(int i=0;i<n;i++){
      memset(vis,0,sizeof vis);
      if(kuhn(i)){
        res++;
      }
    }
    cout<<res<<endl;
    for(int i=0;i<mxn;i++){
      g[i].clear();
    }
  } 
  return 0;
}