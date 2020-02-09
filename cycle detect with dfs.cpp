///Directed graph

#include<bits/stdc++.h>
using namespace std;
vector<int>graph[1010];
int vis[1010],parent[1010],x,flag=0;
int dfs(int node)
{
    stack<int>st;
    st.push(node);
    vis[node]=0;
    while(!st.empty())
    {
        x=st.top(),flag=0;
        for(int i=0;i<graph[x].size();i++)
        {
            if(vis[graph[x][i]]==0)
            {
                parent[graph[x][i]]=x;
                return graph[x][i];
            }
            else if(vis[graph[x][i]]==-1)
            {
                st.push(graph[x][i]);
                vis[graph[x][i]]=0;
                parent[graph[x][i]]=x;
                flag=1;
            }
        }
        if(flag==0)
        {
            vis[st.top()]=1;
            st.pop();
        }
    }
    return -1;
}
int main()
{
    int node,edge,u,v;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        graph[u].push_back(v);
    }
    /*for(int i=1;i<=node;i++)
    {
        cout<<i<<" :  ";
        for(int j=0;j<graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }*/
    memset(vis,-1,sizeof vis);
    int m=dfs(1);
    for(int i=1;i<=node;i++)
            cout<<i<<"  :  "<<parent[i]<<endl;
    int g=m;
    if(m==-1)
        cout<<"no cycle"<<endl;
    else
    {
        stack<int>cycle;
        cycle.push(m);
        m=parent[m];
        while(m!=g)
        {
            cycle.push(m);
            m=parent[m];
        }
        g=cycle.top();
        while(!cycle.empty())
        {
            cout<<cycle.top()<<" -> ";
            cycle.pop();
        }
        cout<<g<<endl;
    }
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




