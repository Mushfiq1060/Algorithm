/**Ques link: https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/the-grass-type/description/  **/

/**In this problem we save the information of bigchild and iterate over small child (jekhane src ke LCA rekhe 
   small child theke big child e gese eirokom path)...after iteration 
   add small child in the big child***/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+5;
vector<int>tree[mxn];
int a[mxn],sbtr[mxn],ord[mxn],euler[mxn],t=1;
unordered_map<int,int>mp;
ll ans=0;
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
    int mx=-1,bg=-1;
    for(int i=0;i<tree[src].size();i++)
        if(sbtr[tree[src][i]]>mx && tree[src][i]!=par)
        {
            mx=sbtr[tree[src][i]];
            bg=tree[src][i];
        }
    for(int i=0;i<tree[src].size();i++)
        if(tree[src][i]!=bg && tree[src][i]!=par)
            dsu(tree[src][i],src,false);
    if(bg!=-1)
        dsu(bg,src,true);
    for(int i=0;i<tree[src].size();i++)
    {
        int xd=tree[src][i];
        if(xd==par || xd==bg)
            continue;
        for(int j=ord[xd];j<=ord[xd]+sbtr[xd]-1;j++)
        {
            int res=a[src]/a[euler[j]];
            if(a[euler[j]]*res==a[src] && mp.count(res))
                ans+=mp[res];
        }
        for(int j=ord[xd];j<=ord[xd]+sbtr[xd]-1;j++)
            mp[a[euler[j]]]++;
    }
    if(mp.count(1))
        ans+=mp[1]; /***this if block is need for src theke src ke LCA rekhe big child e jaoar pair count er jonno**/
    mp[a[src]]++;
    if(!keep)
        mp.clear();
}
int main()
{
    int node;
    scanf("%d",&node);
    for(int i=0;i<node-1;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    for(int i=1;i<=node;i++)
        scanf("%d",a+i);
    dfs(1,0);
    dsu(1,0,false);
    printf("%lld\n",ans);
    return 0;
}