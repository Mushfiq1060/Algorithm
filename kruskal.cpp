#include<bits/stdc++.h>
using namespace std;
const int mxn=1e4;
struct info
{
    int u,v,w;
};
vector<info>arr,mst_path;
int parent[mxn];
bool cmp(info a,info b)
{
    return a.w<b.w;
}
int find_parent(int xd)
{
    if(parent[xd]==xd)
        return xd;
    parent[xd]=find_parent(parent[xd]);
    return parent[xd];
}
int kruskal(int node)
{
    for(int i=0;i<mxn;i++)
        parent[i]=i;
    int cn=0,s=0;
    for(int i=0;i<arr.size();i++)
    {
        int par_u,par_v;
        par_u=find_parent(arr[i].u);
        par_v=find_parent(arr[i].v);
        if(par_u!=par_v)
        {
            parent[par_u]=par_v;
            cn++;
            s+=arr[i].w;
            mst_path.push_back(arr[i]);
        }
        if(cn==node-1)
            break;
    }
    return s;
}
int main()
{
    int node,edge;
    scanf("%d%d",&node,&edge);
    for(int i=0;i<edge;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        info get;
        get.u=u;
        get.v=v;
        get.w=w;
        arr.push_back(get);
    }
    sort(arr.begin(),arr.end(),cmp);
    printf("Minimum spanning tree cost : %d\n",kruskal(node));
    printf("Minimum spanning tree edges : \n");
    for(int i=0;i<mst_path.size();i++)
        printf("%d %d %d\n",mst_path[i].u,mst_path[i].v,mst_path[i].w);
    return 0;
}