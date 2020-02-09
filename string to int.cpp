#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    string str;
    cin>>str;
    ll num=0,i,l;
    l=str.size();
    for(i=0;i<l;i++)
        num=num*10+(str[i]-'0');
    cout<<num<<endl;
    return 0;
}
