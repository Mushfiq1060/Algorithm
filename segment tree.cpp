#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll seg_tree[50],arr[]={4,-9,3,7,1,0,2},cn=0;
void Build_tree(ll left,ll right,ll pos)
{
    cout<<++cn<<" : "<<left<<" "<<right<<endl;
    if(left==right)
    {
        seg_tree[pos]=arr[left];
        return ;
    }
    ll mid=(left+right)/2;
    Build_tree(left,mid,2*pos+1);
    Build_tree(mid+1,right,2*pos+2);
    seg_tree[pos]=seg_tree[2*pos+1]+seg_tree[2*pos+2];
}
int main()
{
    Build_tree(0,6,0);
    for(int i=0;i<=12;i++)
        cout<<seg_tree[i]<<" ";
    return 0;
}
