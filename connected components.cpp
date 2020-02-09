///Undirected graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1010];
int node,edge,vis[1010];
void dfs(int vertex)
{
    vis[vertex]=1;
    for(int i=0;i<graph[vertex].size();i++)
        if(vis[graph[vertex][i]]==-1)
        {
            dfs(graph[vertex][i]);
        }
}
int init()
{
    int component=0;
    memset(vis,-1,sizeof vis);
    for(int i=1;i<=node;i++)
        if(vis[i]==-1)
        {
            dfs(i);
            component++;
        }
    return component;
}
int main()
{
    int u,v;
    cin>>node>>edge ;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cout<<init()<<endl;
    return 0;
}
/**input:
7 5
1 2
1 4
2 3
3 4
5 6
**/
