#include<bits/stdc++.h>
#define ll long long
#define _size 100100
using namespace std;
ll arr[_size];
vector<ll>tree[4*_size];
void Merge(ll idx,ll l,ll r)
{
    ll i=0,j=0;
    while(i<tree[l].size() && j<tree[r].size())
    {
        if(tree[l][i]<tree[r][j])
            tree[idx].push_back(tree[l][i++]);
        else
            tree[idx].push_back(tree[r][j++]);
    }
    while(i<tree[l].size())
        tree[idx].push_back(tree[l][i++]);
    while(j<tree[r].size())
        tree[idx].push_back(tree[r][j++]);
}
void build(ll left,ll right,ll idx)
{
    if(left==right)
    {
        tree[idx].push_back(arr[left]);
        return ;
    }
    ll mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    Merge(idx,idx*2+1,idx*2+2);
}
int main()
{
    ll n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    build(0,n-1,0);
    for(int i=0;i<=14;i++)
    {
        cout<<i<<"  :  ";
        for(int j=0;j<tree[i].size();j++)
            cout<<tree[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
