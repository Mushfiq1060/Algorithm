/**Update value in position x and find the number of integer 
   in range (l-r)  which is greater than k**/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e4+10;
int arr[3*mxn],fenwick[180][mxn];
void update(int block,int idx,int val)
{
    while(idx>0)
    {
        fenwick[block][idx]+=val;
        idx-=(idx&-idx);
    }
}
int query(int block,int idx)
{
    int sum=0;
    while(idx<mxn)
    {
        sum+=fenwick[block][idx];
        idx+=(idx&-idx);
    }
    return sum;
}
int main()
{
    int n;
    scanf("%d",&n);   
    int block_size=500;///arbritrary block size
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        update(i/block_size,arr[i],1);
    }
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int t;
        scanf("%d",&t);
        if(t==0)
        {
            int l,v;
            scanf("%d%d",&l,&v);
            l--;
            update(l/block_size,arr[l],-1);
            arr[l]=v;
            update(l/block_size,arr[l],1);
        }
        else 
        {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            l--,r--;
            int ans=0;
            while(l%block_size!=0 && l<=r)
                ans+=arr[l]>k,l++;
            while(r%block_size!=block_size-1 && l<=r) 
                ans+=arr[r]>k,r--;/*block_size-1 because here it is 0 based indexing if block size is 2
                                    then 1st block is (0-1) and 2nd block is (2-3) so right bound is not 
                                    divisble by block len*/
            if(l<r)
            {
                int bl=l/block_size,br=r/block_size;
                for(int i=bl;i<=br;i++)
                    ans+=query(i,k+1);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}