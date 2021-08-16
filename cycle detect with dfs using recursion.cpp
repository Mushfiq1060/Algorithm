#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
vector<int>adj[mxn];
int vis[mxn],par[mxn],node;
bool flag;
void dfs(int src)
{
  vis[src]=0;
  for(int i=0;i<adj[src].size();i++)
  {
    if(vis[adj[src][i]]==-1)
    {
      if(!flag)
        par[src]=adj[src][i];
      dfs(adj[src][i]);
    }
    else if(vis[adj[src][i]]==0)
    {
      if(!flag)
      {
        flag=true;
        node=adj[src][i];
        par[src]=adj[src][i];
      }
    }
  }
  vis[src]=1;
}
int main()
{
  int n,m;
  cin>>n>>m;
  for(int i=0;i<m;i++)
  {
    int u,v;
    cin>>u>>v;
    adj[u].push_back(v);
  } 
  memset(vis,-1,sizeof vis);
  for(int i=1;i<=n;i++)
  { 
    if(vis[i]==-1)
    {
      flag=false;
      dfs(i);
      if(flag)
      {
        int xd=node;
        vector<int>res;
        res.push_back(xd);
        while(par[node]!=xd)
        {
          res.push_back(par[node]);
          node=par[node];
        }
        res.push_back(xd);
        cout<<res.size()<<endl;
        for(int i=0;i<res.size();i++)
          cout<<res[i]<<" ";
        cout<<endl;
        return 0;
      }
    }
  } 
  cout<<"IMPOSSIBLE"<<endl;
  return 0;
}
