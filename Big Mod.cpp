#include<bits/stdc++.h>
#define ll long long
#define mod 17
using namespace std;
ll Bigmod(ll x,ll y)
{
    if(y==0)
        return 1;
    else if(y%2==0)
    {
        ll p=Bigmod(x,y/2);
        return ((p%mod)*(p%mod))%mod;
    }
    else
        return ((x%mod)*(Bigmod(x,y-1)%mod))%mod;
}
int main()
{
    ll x,y;
    while(1)
    {
        cin>>x>>y;
        cout<<Bigmod(x,y)<<endl;
    }
    return 0;
}
