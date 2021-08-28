///map key as a user defined data type

#include<bits/stdc++.h>
using namespace std;
struct info
{
  int a,b,c;
  bool operator<(const info& p)const
  {
    return this->a<p.a;
  }
};
int main()
{
  map<info,int>mp;
  int n;
  cin>>n;
  for(int i=0;i<n;i++)
  {
    int x,y,z;
    cin>>x>>y>>z;
    mp[{x,y,z}]=1;
  } 
  int dx,dy,dz;
  cin>>dx>>dy>>dz;
  mp.erase({dx,dy,dz});
  for(auto it=mp.begin();it!=mp.end();it++)
    cout<<it->first.a<<" "<<it->first.b<<" "<<it->first.c<<endl;
  return 0;
}
