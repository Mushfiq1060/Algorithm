#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int arr[mxn],len,sum=0;
struct info
{
    int l,r,idx;
}query[mxn];
bool cmp(info a,info b)
{
    int block_own=a.l/len,block_other=b.l/len;
    if(block_own==block_other)
        return a.r<b.r;
    return  block_own<block_other;
}
void add(int idx)
{
    sum+=arr[idx];
}
void remove(int idx)
{
    sum-=arr[idx];
}
int main()
{
    int n;
    scanf("%d",&n);
    len=sqrt(n);
    for(int i=0;i<n;i++)
        scanf("%d",arr+i);
    int q;
    scanf("%d",&q); /**Number of query**/
    for(int i=0;i<q;i++)
        scanf("%d%d",&query[i].l,&query[i].r),query[i].idx=i;
    sort(query,query+q,cmp);
    int left=0,right=-1,ans[q];
    for(int i=0;i<q;i++)
    {
        while(right<query[i].r)
            add(++right);
        while(right>query[i].r)
            remove(right--);
        while(left<query[i].l)
            remove(left++);
        while(left>query[i].l)
            add(--left);
        ans[query[i].idx]=sum;
    }
    for(int i=0;i<q;i++)
        printf("%d\n",ans[i]);
    return 0;
}