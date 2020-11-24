#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1010;
vector<int>adj[mxn];
bool vis[mxn];
int height[mxn],order[mxn],tree[8*mxn];
vector<int>euler;
void dfs(int src,int h)
{
    height[src]=h;
    vis[src]=1;
    order[src]=euler.size();
    euler.push_back(src);
    for(int i=0;i<adj[src].size();i++)  
        if(!vis[adj[src][i]])
        {
            dfs(adj[src][i],h+1);
            euler.push_back(src);
        }
}
void build(int left,int right,int idx)
{
    if(left==right)
    {
        tree[idx]=euler[left];
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    int l=tree[idx*2+1],r=tree[idx*2+2];
    tree[idx]=(height[l]<height[r]?l:r);
}
int query(int left,int right,int ql,int qr,int idx)
{
    if(qr<left || ql>right)
        return -1;
    if(ql<=left && qr>=right)
        return tree[idx];
    int mid=(left+right)/2,l,r;
    l=query(left,mid,ql,qr,idx*2+1);
    r=query(mid+1,right,ql,qr,idx*2+2);
    if(l==-1)
        return r;
    if(r==-1)
        return l;
    return (height[l]<height[r]?l:r);
}
int main()
{   
    int node,edge;
    cin>>node>>edge;
    for(int i=0;i<edge;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(vis,false,sizeof vis);
    dfs(1,0); //imagine root node is 1

    /*cout<<"Euler Array -> ";
    for(int i=0;i<euler.size();i++)
        cout<<euler[i]<<" ";
    cout<<endl;
    cout<<"Height Array -> ";
    for(int i=1;i<=node;i++)
        cout<<height[i]<<" ";
    cout<<endl;
    cout<<"Order in DFS -> ";
    for(int i=1;i<=node;i++)
        cout<<order[i]<<" ";
    cout<<endl;*/

    build(0,euler.size()-1,0);

    /*cout<<"Segment Tree -> "<<endl;
    for(int i=0;i<29;i++)
        cout<<tree[i]<<" ";
    cout<<endl;*/

    int q;
    cin>>q; //how many query
    while(q--)
    {
        int node1,node2;
        cin>>node1>>node2;
        int pos1=order[node1],pos2=order[node2];
        if(pos1>pos2)
            swap(pos1,pos2);
        cout<<query(0,euler.size()-1,pos1,pos2,0)<<endl;
    }
    return 0;
}

/**
Input
18 17
1 4
1 5
1 6
4 12
4 14
14 13
14 17
13 15
13 16
5 7
5 8
8 9
9 3
6 10
10 11
10 18
18 2
10
12 2
12 4
14 11
7 8
7 3
4 6
15 16
17 18
1 6
12 16

Output
1
4
1
5
5
1
13
1
1
4
**/