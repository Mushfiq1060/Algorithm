///Directed graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1010];
int vis[1010],n,parent[1010],val;
bool flag;
void dfs(int node)
{
    vis[node]=0;
    for(int i=0;i<graph[node].size();i++)
    {
        if(vis[graph[node][i]]==-1)
        {
            parent[graph[node][i]]=node;
            dfs(graph[node][i]);
        }
        else if(vis[graph[node][i]]==0)
        {
            flag=true;
            parent[graph[node][i]]=node;
            val=node;
        }
    }
    vis[node]=1;
}
int main()
{
    int node,edge;
    cin>>node>>edge;
    n=node;
    for(int i=0;i<edge;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
    }
    memset(vis,-1,sizeof vis);
    for(int i=1;i<=node;i++)
        if(vis[i]==-1)
        {
            flag=false;
            dfs(i);
            if(flag)
            {
                int xd=val;
                cout<<"YES"<<endl;
                cout<<val<<" ";
                while(parent[val]!=xd)
                {
                    cout<<parent[val]<<" ";
                    val=parent[val];
                }
                return 0;
            }
        }
    cout<<"NO"<<endl;
    return 0;
}
/**
8 8
1 2
2 3
3 7
3 8
3 4
5 4
4 6
8 1
**/
