///Directed graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1010],rev_graph[1010],arr;
int component[1010];
bool vis[1010];
void dfs(int node)
{
    vis[node]=1;
    for(int i=0;i<graph[node].size();i++)
        if(!vis[graph[node][i]])
            dfs(graph[node][i]);
    arr.push_back(node);
}
void dfs2(int node,int cn)
{
    vis[node]=1;
    component[node]=cn;
    for(int i=0;i<rev_graph[node].size();i++)
        if(!vis[rev_graph[node][i]])
            dfs2(rev_graph[node][i],cn);
}
int main()
{
    int node,edge,u,v;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    memset(vis,0,sizeof vis);
    for(int i=1;i<=node;i++)
        if(!vis[i])
            dfs(i);
    memset(vis,0,sizeof vis);
    int cn=0;
    for(int i=arr.size()-1;i>=0;i--)
        if(!vis[arr[i]])
            dfs2(arr[i],++cn);
    for(int i=1;i<=node;i++)
        cout<<i<<"  :  "<<component[i]<<endl;
    return 0;
}
