///Undirected graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1010];
int parent[1010];
bool bfs(int node)
{
    int vis[1000];
    memset(vis,-1,sizeof vis);
    queue<int>qu;
    qu.push(node);
    vis[node]=0;
    while(!qu.empty())
    {
        int x=qu.front();
        qu.pop();
        vis[x]=1;
        for(int i=0;i<graph[x].size();i++)
        {
            if(vis[graph[x][i]]==0)
                return true;
            else if(vis[graph[x][i]]==-1)
            {
                qu.push(graph[x][i]);
                parent[graph[x][i]]=x;
                vis[graph[x][i]]=0;
            }
        }
    }
    return false;
}
int main()
{
    int node,edge,u,v;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i=1;i<=node;i++)
    {
        cout<<i<<" -> ";
        for(int j=0;j<graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }
    if(bfs(1))
        cout<<"Cycle found"<<endl;
    else
        cout<<"Not found"<<endl;
    return 0;
}
/**input :
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
