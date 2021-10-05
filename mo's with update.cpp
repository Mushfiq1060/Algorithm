/*https://toph.co/p/distinct-dishting*/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int n,q,a[mxn],len,_time,l,r;
ll res=0,ans[mxn];
unordered_map<int,int>mp;
struct info
{
  int l,r,id,t;
}Q[mxn];
struct upd
{
  int pos,old,cur;
}U[mxn];
bool cmp(info x,info y)
{
  int b_xl=x.l/len,b_xr=x.r/len,b_yl=y.l/len,b_yr=y.r/len;
  if(b_xl==b_yl)
  {
    if(b_xr==b_yr)
      return x.t<y.t;
    return b_xr<b_yr;
  }
  return b_xl<b_yl;
}
inline void add(int val)
{
  if(val%3==0)
  {
    res+=(mp[val]==0?(ll)val:0);
    mp[val]++;
  }
}
inline void del(int val)
{ 
  if(val%3==0)
  {
    mp[val]--;
    res-=(mp[val]==0?(ll)val:0); 
  }
}
inline void update(int pos,int x)
{
  if(l<=pos && pos<=r)
  {
    add(x);
    del(a[pos]);
  }
  a[pos]=x;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin>>n>>q;
  for(int i=1;i<=n;i++)
    cin>>a[i];
  int nq=0,nu=0;
  for(int i=1;i<=q;i++)
  {
    int ty,l,r;
    cin>>ty>>l>>r;
    if(ty==0)
    {
      nu++;
      U[nu].pos=l;
      U[nu].old=a[l];
      a[l]=r;
      U[nu].cur=a[l];
    }
    else
    {
      nq++;
      Q[nq]={l,r,nq,nu};
    }
  }
  len=sqrt(n)+10;
  sort(Q+1,Q+nq+1,cmp);
  _time=nu,l=1,r=0;
  for(int i=1;i<=nq;i++)
  {
    while(_time<Q[i].t)
      _time++,update(U[_time].pos,U[_time].cur);
    while(_time>Q[i].t)
      update(U[_time].pos,U[_time].old),_time--;
    while(l>Q[i].l)
      add(a[--l]);
    while(l<Q[i].l)
      del(a[l++]);
    while(r<Q[i].r)
      add(a[++r]);
    while(r>Q[i].r)
      del(a[r--]);
    ans[Q[i].id]=res;
  }
  for(int i=1;i<=nq;i++)
    cout<<ans[i]<<endl;
  return 0;
}
