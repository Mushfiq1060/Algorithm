#include<bits/stdc++.h>
using namespace std;
int node,edge,m,color[20];
vector<int>graph[20];
bool is_safe(int c,int idx)
{
    for(int i=0;i<graph[idx].size();i++)
        if(c==color[graph[idx][i]])
            return false;
    return true;
}
bool graph_color(int idx)
{
    if(idx>node)
        return true;
    for(int i=1;i<=m;i++)
        if(is_safe(i,idx))
        {
            //cout<<"-> "<<idx<<" "<<i<<endl;
            color[idx]=i;
            if(graph_color(idx+1))
                return true;
            color[idx]=0;
        }
    return false;
}
int main()
{
    cin>>node>>edge>>m;
    for(int i=0;i<edge;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    memset(color,0,sizeof color);
    if(graph_color(1))
    {
        cout<<"Color of node is : "<<endl;
        for(int i=1;i<=node;i++)
            cout<<i<<" -> "<<color[i]<<endl;
    }
    else
        cout<<"No color"<<endl;
    return 0;
}
/**
This input is not colourable
5 8 3
1 2
1 3
2 3
2 4
2 5
3 5
4 5
3 4
**/
/**
This input is colourable
5 7 3
1 2
1 3
2 3
2 4
2 5
3 5
4 5
**/
