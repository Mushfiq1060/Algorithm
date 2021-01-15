#include<bits/stdc++.h>
#define _size 100100
#define ll long long
using namespace std;
struct info
{
    ll val,prop;
};
info tree[4*_size];
ll arr[_size];
void build_tree(ll left,ll right,ll idx)
{
    if(left==right)
    {
        tree[idx].val=arr[left];
        tree[idx].prop=0;
        return ;
    }
    ll mid=(left+right)/2;
    build_tree(left,mid,idx*2+1);
    build_tree(mid+1,right,idx*2+2);
    tree[idx].val=tree[idx*2+1].val+tree[idx*2+2].val;
    tree[idx].prop=0;
}
void update(ll left,ll right,ll ql,ll qr,ll x,ll idx)
{
    if(qr<left || ql>right)
        return;
    else if(ql<=left && qr>=right)
    {
        tree[idx].val+=((right-left+1)*x);
        tree[idx].prop+=x;
        return ;
    }
    ll mid=(left+right)/2;
    update(left,mid,ql,qr,x,idx*2+1);
    update(mid+1,right,ql,qr,x,idx*2+2);
    tree[idx].val=tree[idx*2+1].val+tree[idx*2+2].val+tree[idx].prop*(right-left+1);
}
ll Query(ll left,ll right,ll ql,ll qr,ll idx,ll carry)
{
    if(ql>right || qr<left)
        return 0;
    else if(ql<=left && qr>=right)
        return tree[idx].val+(right-left+1)*carry;
    ll mid=(left+right)/2,p,q;
    p=Query(left,mid,ql,qr,idx*2+1,carry+tree[idx].prop);
    q=Query(mid+1,right,ql,qr,idx*2+2,carry+tree[idx].prop);
    return p+q;
}
int main()
{
    ll t,_case=0;
    scanf("%lld",&t);
    while(t--)
    {
        ll n,q;
        scanf("%lld %lld",&n,&q);
        memset(arr,0,sizeof arr);
        build_tree(0,n-1,0);
        printf("Case %lld:\n",++_case);
        while(q--)
        {
            ll p;
            scanf("%lld",&p);
            if(p==0)
            {
                ll l,r,x;
                scanf("%lld %lld %lld",&l,&r,&x); ///update range l to r with value x
                update(0,n-1,l,r,x,0);
            }
            else
            {
                ll l,r,val;
                scanf("%lld %lld",&l,&r);
                val=Query(0,n-1,l,r,0,0);///sum range l to r
                printf("%lld\n",val);
            }
        }
    }
    return 0;
}