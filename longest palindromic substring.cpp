/*Complexity: nlogn*/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e6+10,mod=1000004119,base=31;
int n,pwr[mxn],pref[mxn],suff[mxn];
inline int add(int val1,int val2)
{
  if(val1<0) val1+=mod; 
  if(val2<0) val2+=mod; 
  if(val1+val2>=mod) return val1+val2-mod;
  return val1+val2;
}
inline int mul(int val1,int val2)
{
  if(val1<0) val1+=mod;
  if(val2<0) val2+=mod;
  return ((ll)((ll)val1*(ll)val2))%mod;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  string str;
  cin>>str;
  n=str.size();
  pwr[0]=1;
  for(int i=1;i<=n;i++)
    pwr[i]=mul(pwr[i-1],base);
 
  ////build suffix hash 
  suff[n]=0;
  for(int i=n-1;i>=0;i--)
    suff[i]=add((str[i]-'a'+1),mul(suff[i+1],base));
 
  ///build prefix hash
  pref[0]=str[0]-'a'+1;
  for(int i=1;i<n;i++)
    pref[i]=add((str[i]-'a'+1),mul(pref[i-1],base));
 
  int res=0;
 
  //check for odd length longest palindrome
  for(int i=0;i<n;i++)
  {
    int lc=i,rc=n-i,left=0,right=min(lc,rc);
    while(left<=right)
    {
      int mid=(left+right)/2;
      int l=i+1,r=i+mid;
      int forward_hash=add(suff[l]-mul(suff[r+1],pwr[r-l+1]),mod);
      l=i-mid,r=i-1;
      int reverse_hash=add(pref[r]-mul((l!=0?pref[l-1]:0),pwr[r-l+1]),mod);
      if(forward_hash==reverse_hash)
      {
        res=max(res,2*mid+1);
        left=mid+1;
      }
      else  
        right=mid-1;
    }
  }
  
  //check for even length longest palindrome
  for(int i=0;i<n;i++)
  {
    int lc=i,rc=n-i+1,left=0,right=min(lc,rc);
    while(left<=right)
    {
      int mid=(left+right)/2;
      int l=i,r=i+mid-1;
      int forward_hash=add(suff[l]-mul(suff[r+1],pwr[r-l+1]),mod);
      l=i-mid,r=i-1;
      int reverse_hash=add(pref[r]-mul((l!=0?pref[l-1]:0),pwr[r-l+1]),mod);
      if(forward_hash==reverse_hash)
      {
        res=max(res,2*mid);
        left=mid+1;
      }
      else  
        right=mid-1;
    }
  }
 
  string ans="";
  for(int i=0;i<n;i++)
  {
    if(i+res-1>=n)
      break;
    int l=i,r=i+res-1;
    int forward_hash=add(suff[l]-mul(suff[r+1],pwr[r-l+1]),mod);
    int reverse_hash=add(pref[r]-mul((l!=0?pref[l-1]:0),pwr[r-l+1]),mod);
    if(forward_hash==reverse_hash)
    {
      for(int j=i;j<=i+res-1;j++)
        ans+=str[j];
      break;
    }
  }
  cout<<ans<<endl;
 
  return 0;
}
/*
 
  str = "yarqs" , p=base
 
  suffix hash array:
 
                    s = s*p^0
                   qs = q*p^0 + s*p^1
                  rqs = r*p^0 + q*p^1 + s*p^2
                 arqs = a*p^0 + r*p^1 + q*p^2 + s*p^3
                yarqs = y*p^0 + a*p^1 + r*p^2 + q*p^3 + s*p^4
 
 
  prefix hash array: 
                    y =                                 y*p^0
                   ya =                         y*p^1 + a*p^0
                  yar =                 y*p^2 + a*p^1 + r*p^0
                 yarq =         y*p^3 + a*p^2 + r*p^1 + q*p^0
                yarqs = y*p^4 + a*p^3 + r*p^2 + q*p^1 + s*p^0
 
 
  gethash(l,r) => suff[l]-(suff[r+1]*pwr[r-l+1]) -> (r>l) -> finding forward hash
 
  gethash(r,l) => pref[r]-(pref[l-1]*pwr[r-l+1]) -> (r>l) -> finding reverse hash
 
 
*/
