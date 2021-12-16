#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=2e5+10;
int arr[mxn];
struct info
{
    ll sum,pref,suff,ans;
    /*
        sum = all node sum under subtree
        pref = best prefix under subtree
        suff = best suffix under subtree
        ans = best answer in the current node
    */
}tree[4*mxn];
void func(int idx)
{
    int l=idx*2+1,r=idx*2+2;
    tree[idx].sum=tree[l].sum+tree[r].sum;
    tree[idx].pref=max(tree[l].pref,tree[l].sum+tree[r].pref);
    tree[idx].suff=max(tree[r].suff,tree[r].sum+tree[l].suff);
    tree[idx].ans=max({tree[l].sum+tree[r].sum,tree[l].ans,tree[r].ans,tree[l].suff+tree[r].pref});//left part ans,right part ans & overlaping part ans
}
void build(int left,int right,int idx)
{
    if(left==right)
    {
        tree[idx]={arr[left],arr[left],arr[left],arr[left]};
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    func(idx);
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)
        scanf("%d",arr+i);
    build(0,n-1,0);
    printf("%lld\n",tree[0].ans);
    return 0;
}
