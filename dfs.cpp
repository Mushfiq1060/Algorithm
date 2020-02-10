///Directed graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1000],traverse;
stack<int>st;
int vis[1000]={false};
void dfs(int node)
{
    memset(vis,-1,sizeof vis);
    st.push(node);
    vis[node]=0;
    while(!st.empty())
    {
        int x=st.top(),flag=0;
        for(int i=0;i<graph[x].size();i++)
            if(vis[graph[x][i]]==-1)
            {
                st.push(graph[x][i]);
                vis[graph[x][i]]=0;
                flag=1;
            }
        if(flag==0)
        {
            traverse.push_back(st.top());
            st.pop();
        }
    }
}
/*void dfsRecursive(int src){
    if(!vis[src])
    {
        vis[src] = true ;
        for(int i=0;i<graph[src].size();i++)
                dfsRecursive(i) ;
        cout<<src<<" ";
    }
}*/
int main()
{
    int node,edge,u,v;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        //graph[v].push_back(u);
    }
    for(int i=1;i<=node;i++)
    {
        cout<<i<<"   :   ";
        for(int j=0;j<graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }
    dfs(1);
    for(int i=traverse.size()-1;i>=0;i--)
        cout<<traverse[i]<<" ";
    return 0;
}
/**6 7
1 2
1 4
1 6
2 4
4 3
4 5
3 5**/
