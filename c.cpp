/**Modular inverse factorial and dearrangement**/

/**
 * derangement is a permutation of the elements of a set, such that no element appears in its original position
 *  
 * 1 2 3 4 5
 *------------
 * 2 1 4 3 5 -> it is not a dearranement because 5 presents under 5
 * 2 1 4 5 3 -> it is a dearrangemet
 * 
 * number of dearrangement = n!/e  -> where n is length of set and e=2.718.....
 * 
 * drang(n)=(n-1)*(drang(n-1)+drang(n-2))
 * base case -> drang(0)=1,drang(1)=0,drang(2)=1;
 * 
**/


#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e3+10,mod=1e9+7;
ll fact[mxn],invFact[mxn],drang[mxn];
ll bigmod(int n,int m)
{
  if(m==0)
    return (ll)1;
  if(m%2==0)
  {
    ll p=bigmod(n,m/2);
    return (p%mod*p%mod)%mod;
  }
  return (n%mod*bigmod(n,m-1)%mod)%mod;
}
void func()
{
  fact[0]=1;
  invFact[0]=1;
  for(int i=1;i<mxn;i++)
  {
    fact[i]=(fact[i-1]%mod*i%mod)%mod;
    invFact[i]=bigmod(fact[i],mod-2);
  }
  drang[0]=1;
  drang[1]=0;
  drang[2]=1;
  for(int i=3;i<mxn;i++)
    drang[i]=((i-1)%mod*(drang[i-1]+drang[i-2])%mod)%mod;
}
int main()
{
  func();
  return 0;
}
