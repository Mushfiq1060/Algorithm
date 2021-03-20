/**How many elements are smaller or equal in the left of current element**/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
int arr[mxn];
vector<int>tree[4*mxn];
void Merge(int idx)
{
    int l=idx*2+1,r=idx*2+2,i=0,j=0;
    while(i<tree[l].size() && j<tree[r].size())
    {
        if(tree[l][i]<tree[r][i])
            tree[idx].push_back(tree[l][i]),i++;
        else
            tree[idx].push_back(tree[r][j]),j++;
    }
    while(i<tree[l].size())
        tree[idx].push_back(tree[l][i]),i++;
    while(j<tree[r].size())
        tree[idx].push_back(tree[r][j]),j++;
}
void build(int left,int right,int idx)
{
    if(left==right)
    {
        tree[idx].push_back(arr[left]);
        return ;
    }
    int mid=(left+right)/2;
    build(left,mid,idx*2+1);
    build(mid+1,right,idx*2+2);
    Merge(idx);
}
int query(int left,int right,int idx,int ql,int qr,int val)
{
    if(ql>right || qr<left)
        return 0;
    if(ql<=left && qr>=right)
    {
        int pos=upper_bound(tree[idx].begin(),tree[idx].end(),val)-tree[idx].begin();
        return pos;
    }
    int mid=(left+right)/2,p,q;
    p=query(left,mid,idx*2+1,ql,qr,val);
    q=query(mid+1,right,idx*2+2,ql,qr,val);
    return p+q;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    build(0,n-1,0);
    int res[n];
    res[0]=0;
    for(int i=1;i<n;i++)
        res[i]=query(0,n-1,0,0,i-1,arr[i]);
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" -> "<<res[i]<<endl;
    return 0;
}

/***
Input: 
10
2 3 5 4 1 6 9 7 5 1

Output:
2 -> 0
3 -> 1
5 -> 2
4 -> 1
1 -> 0
6 -> 5
9 -> 6
7 -> 6
5 -> 5
1 -> 1

**/