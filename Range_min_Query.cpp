///with segment tree

#include<bits/stdc++.h>
#define ll long long
#define _size 4000050
#define INF 1e12
using namespace std;
ll arr[_size],seg_tree[_size];
void Build_tree(ll left,ll right,ll pos)
{
    if(left==right)
    {
        seg_tree[pos]=arr[left];
        return ;
    }
    ll mid=(left+right)/2;
    Build_tree(left,mid,2*pos+1);
    Build_tree(mid+1,right,2*pos+2);
    seg_tree[pos]=min(seg_tree[2*pos+1],seg_tree[2*pos+2]);
}
ll range_min_query(ll q_low,ll q_high,ll left,ll right,ll pos)
{
    if(q_low>right || q_high<left)///no overlap so return a infinite value.Because we cannot find answer in this node.
        return INF;
    if(q_low<=left && q_high>=right)///totally overlap so return the current pos value.Because in this node minimum value stored of every child node of this node.
        return seg_tree[pos];
    ll mid=(left+right)/2;
    ll p,q;

    ///partially overlap so we can check the child of this node
    p=range_min_query(q_low,q_high,left,mid,2*pos+1);
    q=range_min_query(q_low,q_high,mid+1,right,2*pos+2);
    return min(p,q);
}
int main()
{
    ll n,t,i,query;
    cin>>t;
    while(t--){
    cin>>n>>query;
    for(i=0;i<n;i++)
        cin>>arr[i];
    Build_tree(0,n,0);
    for(i=0;i<=12;i++)
        cout<<seg_tree[i]<<" ";
    while(query--)
    {
        ll x,y;
        cin>>x>>y;
        cout<<range_min_query(x-1,y-1,0,n,0)<<endl;
    }}
    return 0;
}
