#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=2e5+10;
ll arr[mxn];
struct info
{
    ll val,prop=0;
}tree[4*mxn];
inline void push(int l,int r,int idx)
{
    tree[idx].val+=(r-l+1)*tree[idx].prop;
    if(l!=r)
    {
        tree[2*idx+1].prop+=tree[idx].prop; 
        tree[2*idx+2].prop+=tree[idx].prop;
    }
    tree[idx].prop=0;
}
void build(int left,int right,int idx)
{
    if(left==right)
    {
        tree[idx].val=arr[left];
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    tree[idx].val=tree[idx*2+1].val+tree[idx*2+2].val;
}
void update(int left,int right,int idx,int ql,int qr,int x)
{
    if(tree[idx].prop!=0)
        push(left,right,idx);//pushing propagrating value in child node and set propagating value 0 in current node
    if(ql>right || qr<left)
        return ;
    if(ql<=left && qr>=right)
    {
        tree[idx].val+=(right-left+1)*x;
        if(left!=right)
        {
            tree[idx*2+1].prop+=x;
            tree[idx*2+2].prop+=x;
        }
        return ;
    }
    int mid=(left+right)/2;
    update(left,mid,idx*2+1,ql,qr,x);
    update(mid+1,right,idx*2+2,ql,qr,x);
    tree[idx].val=tree[idx*2+1].val+tree[idx*2+2].val;
}
ll query(int left,int right,int idx,int ql,int qr)
{
    if(tree[idx].prop!=0)
        push(left,right,idx);
    if(ql>right || qr<left)
        return 0;
    if(ql<=left && qr>=right)
        return tree[idx].val;
    int mid=(left+right)/2;
    return query(left,mid,idx*2+1,ql,qr)+query(mid+1,right,idx*2+2,ql,qr);
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)
        scanf("%lld",arr+i);
    build(0,n-1,0);
    while(q--)
    {
        int t,l,r;
        scanf("%d%d%d",&t,&l,&r);
        if(t==1)
        {
            int x;
            scanf("%d",&x);
            update(0,n-1,0,l,r,x);
        }
        else 
            printf("%lld\n",query(0,n-1,0,l,r));
    }
    return 0; 
}
