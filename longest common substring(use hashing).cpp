/**
 time complexity : nlog^2(n)
**/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mod=1e9+7,base=26;
string s1,s2;
bool func(int len)
{
    int l1=s1.size(),l2=s2.size();
    map<int,bool>mp;
    int hash=0,p=1;
    for(int i=1;i<len;i++)
        p=(p*base)%mod;
    for(int i=0;i<len;i++)
        hash=((hash*base)%mod+(s1[i]-'a'+1))%mod;
    mp[hash]=1;
    for(int i=len;i<l1;i++)
    {
        hash=(mod+hash-((s1[i-len]-'a'+1)%mod*p%mod)%mod)%mod;
        hash=(hash*base)%mod;
        hash=(hash%mod+(s1[i]-'a'+1)%mod)%mod;
        mp[hash]=1;
    }
    hash=0;
    for(int i=0;i<len;i++)
        hash=((hash*base)%mod+(s2[i]-'a'+1))%mod;
    if(mp.count(hash))
            return true;
    for(int i=len;i<l2;i++)
    {
        hash=(mod+hash-((s2[i-len]-'a'+1)%mod*p%mod)%mod)%mod;
        hash=(hash*base)%mod;
        hash=(hash%mod+(s2[i]-'a'+1)%mod)%mod;
        if(mp.count(hash))
            return true;
    }
    return false;
}
int main()
{
    cin>>s1>>s2;
    int left=0,right=min(s1.size(),s2.size()),ans=0;
    while(left<=right)
    {
        int mid=(left+right)/2;
        if(func(mid))
            left=mid+1,ans=mid;
        else    
            right=mid-1;
    }
    cout<<ans<<endl;
    return 0;
}
