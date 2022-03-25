#include<bits/stdc++.h>
#define inf 1000000
using namespace std;
vector<int>graph[1010],weight[1010];
int dist[1010],vis[1010],node,edge;
struct info
{
     int u,v;
     info(int node,int cost)
     {
         u=node;
         v=cost;
     }
     bool operator < ( const info& p ) const {      return v > p.v;   }
};
void dijkstra(int src)
{
    for(int i=0;i<1010;i++)
        dist[i]=inf;
    dist[src]=0;
    priority_queue<info>qu;
    qu.push(info(src,0));
    while(!qu.empty())
    {
        info x=qu.top();
        qu.pop();
        int y=x.u;
        if(vis[y])
             continue;
        vis[y]=1;
        for(int i=0;i<graph[y].size();i++)
        {
            int p=graph[y][i];
            if(dist[y]+weight[y][i]<dist[p])
            {
                dist[p]=dist[y]+weight[y][i];
                qu.push(info(p,dist[p]));
            }
        }
    }
    for(int i=1;i<=node;i++){
        cout<<src<<" --> "<<i<<" = "<<dist[i]<<endl;
    }
}
int main()
{
    int u,v,w;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v>>w;
        graph[u].push_back(v);
        graph[v].push_back(u);
        weight[u].push_back(w);
        weight[v].push_back(w);
    }
    memset(vis,0,sizeof vis);
    dijkstra(node);
    return 0;
}
/**
6 9
1 2 1
1 3 10
2 4 4
1 4 8
3 4 2
3 5 15
4 6 7
4 5 3
5 6 5
**/
