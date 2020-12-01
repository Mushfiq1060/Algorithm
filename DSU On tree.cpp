/***In this problem we find the color x in subtree of node u**/
/***We can solve it using dsu on tree**/
/***We store big subtree in map and iterate small subtree and find ans**/
/**Time complexity O(nlogn)**/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int node,sbtr[mxn],ord[mxn],euler[mxn],color[mxn],ans[mxn],t=1;
vector<int>tree[mxn];
vector<pair<int,int>>query[mxn];
unordered_map<int,int>mp;
void dfs(int src,int par)
{
    sbtr[src]=1;
    ord[src]=t;
    euler[t]=src;
    t++;
    for(int i=0;i<tree[src].size();i++)
        if(tree[src][i]!=par)
        {
            dfs(tree[src][i],src);
            sbtr[src]+=sbtr[tree[src][i]];
        }
}
void dsu(int src,int par,bool keep)
{
    int bg=-1,mx=-1;
    for(int i=0;i<tree[src].size();i++)
    {
        if(tree[src][i]==par)
            continue;
        if(mx<sbtr[tree[src][i]])
        {
            bg=tree[src][i];
            mx=sbtr[tree[src][i]];
        }
    }
    for(int i=0;i<tree[src].size();i++)
    {
        if(tree[src][i]==bg || tree[src][i]==par)
            continue;
        dsu(tree[src][i],src,false);
    }
    if(bg!=-1)
        dsu(bg,src,true);
    for(int i=0;i<tree[src].size();i++)
    {
        if(tree[src][i]==par || tree[src][i]==bg)
            continue;
        int p=tree[src][i];
        for(int j=ord[p];j<=ord[p]+sbtr[p]-1;j++)
        {
            int xd=euler[j];
            mp[color[xd]]++;
        }
    }
    mp[color[src]]++;
    for(int i=0;i<query[src].size();i++)
    {
        int c=query[src][i].first,idx=query[src][i].second;
        ans[idx]=mp[c];
    }
    if(!keep)
        mp.clear();
}
int main()
{
    cin>>node;
    for(int i=1;i<=node;i++)
        cin>>color[i];
    for(int i=0;i<node-1;i++)
    {
        int u,v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1,0);
    int q;
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        int u,x;
        cin>>u>>x;
        query[u].push_back({x,i});
    }
    cout<<"Euler Array -> ";
    for(int i=1;i<=node;i++)
        cout<<euler[i]<<" ";
    cout<<endl;
    dsu(1,0,0);
    for(int i=1;i<=q;i++)
        cout<<ans[i]<<endl;
    return 0;
}
/**

Input : 
17
2 1 1 5 4 1 3 3 4 2 2 2 2 3 1 2 4
1 2
2 5 
5 4
5 6
2 7
7 8
8 10
8 11
8 12
7 9
1 3
3 14
14 16
14 17
3 13
13 15
5
1 2
2 3
14 2
3 2
8 2

Output: 
Euler Array -> 1 2 5 4 6 7 8 10 11 12 9 3 14 16 17 13 15 
6
2
1
2
3

**/
