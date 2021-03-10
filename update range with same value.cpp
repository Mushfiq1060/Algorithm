/**Update range with same value and find the range sum
 * using segment tree with lazy propagation
 **/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
struct info
{
    ll sum=0,prop=-1;
}tree[4*mxn];
void func(int left,int right,int idx)
{
    if(left!=right)
    {
        tree[idx*2+1].prop=tree[idx].prop;
        tree[idx*2+2].prop=tree[idx].prop;
    }
    tree[idx].sum=(right-left+1)*tree[idx].prop;
    tree[idx].prop=-1;
}
void update(int left,int right,int idx,int ul,int ur,ll val)
{
    if(tree[idx].prop!=-1)
        func(left,right,idx); //propagate the value in chile node and set prop -1 in current node
    if(ul>right || ur<left)
        return ;
    if(ul<=left && ur>=right)
    {
        tree[idx].sum=(right-left+1)*val;
        if(left!=right)
        {
            tree[idx*2+1].prop=val;
            tree[idx*2+2].prop=val;
        }
        return ;
    }
    int mid=(left+right)/2;
    update(left,mid,idx*2+1,ul,ur,val);
    update(mid+1,right,idx*2+2,ul,ur,val);
    tree[idx].sum=tree[idx*2+1].sum+tree[idx*2+2].sum;
}
ll query(int left,int right,int idx,int ql,int qr)
{
    if(tree[idx].prop!=-1)
        func(left,right,idx);
    if(ql>right || qr<left)
        return (ll)0;
    if(ql<=left && qr>=right)
        return tree[idx].sum;
    int mid=(left+right)/2,p,q;
    p=query(left,mid,idx*2+1,ql,qr);
    q=query(mid+1,right,idx*2+2,ql,qr);
    return p+q;
}
int main()
{
    int t,_case=0;
    scanf("%d",&t);   
    while(t--)
    {
        int n,q;
        scanf("%d%d",&n,&q);
        printf("Case %d:\n",++_case);
        while(q--)  
        {
            int type;
            scanf("%d",&type);
            if(type==1)
            {
                int l,r;
                ll v;
                scanf("%d%d%lld",&l,&r,&v); //0<=v<=mxn thus prop in structure equal to -1
                update(0,n-1,0,l,r,v);
            }
            else 
            {
                int l,r;
                scanf("%d%d",&l,&r);
                ll val1=query(0,n-1,0,l,r);
                printf("%lld\n",val1);
            }
        }
        for(int i=0;i<4*mxn;i++)
            tree[i].sum=0,tree[i].prop=-1;
    }
    return 0;
}