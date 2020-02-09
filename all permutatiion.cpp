#include<bits/stdc++.h>
#define ll long long
using namespace std;
string str="ABC";
bool taken[3]={0};
void func(int idx,string res="")
{
    if(idx==0)
    {
        cout<<res<<endl;
        return ;
    }
    for(int i=0;i<str.size();i++)
        if(taken[i]==false)
        {
            taken[i]=true;
            func(idx-1,res+str[i]);
            taken[i]=false;
        }
}
int main()
{
    func(3);
    return 0;
}

