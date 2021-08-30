#include<bits/stdc++.h>
using namespace std;
const int mxn=1e5+10;
int phi[mxn];
void phi_sieve()
{
  for(int i=1;i<mxn;i++) 
    phi[i]=i;
  for(int i=2;i<mxn;i++)
    if(phi[i]==i)
    {
      for(int j=i;j<mxn;j+=i)
        phi[j]-=phi[j]/i;
    }
}
int main()
{
    phi_sieve();
    return 0;
}
