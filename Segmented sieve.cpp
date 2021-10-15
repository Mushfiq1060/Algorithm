/** How many prime in a range l to r......(r-l)<=10^5.....1<=r,l<=2^31 */

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=5e4+10;
bool mark[mxn];
vector<int>prime;
void sieve()
{
  mark[0]=mark[1]=1;
  for(int i=2;i<=mxn/i;i++) 
    if(!mark[i])
    {
      for(ll j=i*i;j<mxn;j+=i)
        mark[j]=1;
    }
  for(int i=2;i<mxn;i++)
    if(!mark[i])
      prime.push_back(i);
}
int segmented_sieve(int l,int r)
{
  bool isPrime[r-l+5];
  memset(isPrime,0,sizeof isPrime);
  if(l==1)
    isPrime[l-1]=1;
  for(int i=0;(ll)prime[i]*(ll)prime[i]<=r;i++)
  {
    ll x=(l/prime[i])*prime[i];
    if(x<l)
      x+=prime[i];
    for(ll j=x;j<=r;j+=prime[i])
      isPrime[j-l]=1;
    if(x==prime[i])
      isPrime[x-l]=0;
  }
  int cn=0;
  for(int i=0;i<=r-l;i++)
    if(!isPrime[i])
      cn++;
  return cn;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  sieve(); 
  int t,_case=0;
  cin>>t;
  while(t--)
  {
    ll l,r;
    cin>>l>>r;
    cout<<"Case "<<++_case<<": "<<segmented_sieve(l,r)<<endl;
  }
  return 0;
}
