/**It is used in tree when there is update and query in tree**/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1010;
vector<int>adj[mxn],euler;
int t=0,parent[mxn],depth[mxn],sbtr[mxn],pos[mxn],chainNo=0,chainHead[mxn],chainID[mxn],chainPos[mxn],chainSize[mxn];
void dfs(int src,int par,int lev)
{
    depth[src]=lev;
    parent[src]=par;
    sbtr[src]=1;
    for(int i=0;i<adj[src].size();i++)
        if(par!=adj[src][i])
        {
            dfs(adj[src][i],src,lev+1);
            sbtr[src]+=sbtr[adj[src][i]];
        }
}
void hld(int src,int par)
{
    if(chainHead[chainNo]==-1)
        chainHead[chainNo]=src;
    chainID[src]=chainNo;
    chainPos[src]=chainSize[chainNo];
    chainSize[chainNo]++;
    euler.push_back(src);//heavy chain elements are in consecutive
    pos[src]=t++;//position in euler array
    int mx=0,idx=-1;
    for(int i=0;i<adj[src].size();i++)
        if(adj[src][i]!=par && sbtr[adj[src][i]]>=mx)
        {
            mx=sbtr[adj[src][i]];
            idx=i;
        }
    if(idx!=-1)
        hld(adj[src][idx],src);//first dfs in heavy child which subtree(sbtr) size is max
    for(int i=0;i<adj[src].size();i++)
        if(i!=idx && adj[src][i]!=par)
        {
            chainNo++;
            hld(adj[src][i],src);
        }
}
int main()
{
    int node;
    scanf("%d",&node);
    for(int i=0;i<node-1;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(chainHead,-1,sizeof chainHead);
    dfs(1,0,0);
    hld(1,0);
    for(int i=0;i<euler.size();i++)
        cout<<euler[i]<<" ";
    return 0;
}