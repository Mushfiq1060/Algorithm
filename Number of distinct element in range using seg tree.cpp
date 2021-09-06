/**Number of distinct element in range using segment tree**/
/// Complexity nlogn

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int a[mxn],last[mxn],ans[mxn],tree[4*mxn];
struct info
{
  int l,r,id;
};
vector<info>v;
void update(int left,int right,int idx,int qidx,int val)
{
  if(left==right)
  {
    tree[idx]+=val;
    return;
  }
  int mid=(left+right)/2;
  if(qidx<=mid)
    update(left,mid,idx*2+1,qidx,val);
  else 
    update(mid+1,right,idx*2+2,qidx,val);
  tree[idx]=tree[idx*2+1]+tree[idx*2+2];
}
int query(int left,int right,int idx,int ql,int qr)
{
  if(ql>right || qr<left)
    return 0;
  if(ql<=left && qr>=right)
    return tree[idx];
  int mid=(left+right)/2,p,q;
  p=query(left,mid,idx*2+1,ql,qr);
  q=query(mid+1,right,idx*2+2,ql,qr);
  return p+q;
}
void reset()
{
  memset(tree,0,sizeof tree);
  memset(last,-1,sizeof last);
  v.clear();
}
int main()
{
  int t,_case=0;
  scanf("%d",&t);
  while(t--)
  {
    reset();
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)
      scanf("%d",&a[i]);
    for(int i=0;i<q;i++)
    {
      int l,r;
      scanf("%d%d",&l,&r);
      v.push_back({l-1,r-1,i});
    }
    sort(v.begin(),v.end(),[](info x,info y){
      if(x.r==y.r)
        return x.l<y.l;
      return x.r<y.r;
    });
    int j=0;
    for(int i=0;i<v.size();i++)
    {
      while(j<=v[i].r)
      {
        if(last[a[j]]==-1)
          update(0,n-1,0,j,1);
        else  
        {
          update(0,n-1,0,last[a[j]],-1);
          update(0,n-1,0,j,1);
        }
        last[a[j]]=j;
        j++;
      }
      ans[v[i].id]=query(0,n-1,0,v[i].l,v[i].r);
    }
    printf("Case %d:\n",++_case);
    for(int i=0;i<v.size();i++)
      printf("%d\n",ans[i]);
  }
  return 0;
}
