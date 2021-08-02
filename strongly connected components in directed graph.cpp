/**
strongly connected components are used in directed graph for detecting cycle**/
**/

#include<bits/stdc++.h>
using namespace std;
const int mxn=1050;
vector<int>graph[mxn],rev_graph[mxn],comp;
bool vis[mxn];
stack<int>st;
void dfs(int src)
{
    vis[src]=1;
    for(int i=0;i<graph[src].size();i++)
        if(!vis[graph[src][i]])
            dfs(graph[src][i]);
    st.push(src);
}
void rev_dfs(int src)
{
    vis[src]=1;
    comp.push_back(src);
    for(int i=0;i<rev_graph[src].size();i++)
        if(!vis[rev_graph[src][i]])
            rev_dfs(rev_graph[src][i]);
}
int main()
{
    int node,edge;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    memset(vis,0,sizeof vis);
    for(int i=0;i<node;i++)
        if(!vis[i])
            dfs(i);
    memset(vis,0,sizeof vis);
    while(!st.empty())
    {
        int val=st.top();
        st.pop();
        if(!vis[val])
        {
            rev_dfs(val);
            cout<<val;
            for(int i=comp.size()-1;i>=0;i--)
                cout<<" -> "<<comp[i];
            cout<<endl;
        }
        comp.clear();
    }
    memset(vis,0,sizeof vis);
    return 0;
}

/**
input: 
11 13
1 0
0 2
2 1
0 3
3 5
5 4
4 3
6 4
6 7
7 8
8 9
9 6
9 10



output:
6 -> 7 -> 8 -> 9 -> 6
10 -> 10
0 -> 2 -> 1 -> 0
3 -> 5 -> 4 -> 3
**/
