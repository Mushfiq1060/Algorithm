#include<bits/stdc++.h>
#define ll long long
#define _size 10100
using namespace std;
ll arr[_size],tree[_size];
void update(ll idx,ll val,ll n)
{
    while(idx<=n)
    {
        tree[idx]+=val;///update the value of index
        idx+=(idx & -idx);///2's complement of current index and then logical and(&) operation with ((+idx) & (-idx)) then add the value with previous index

        /** idx(10) : 1010
            -idx(10): 0101  2's complement of 10
                      +  1  add 1
                _____________
                      0110  -idx

            idx(10) :  1010
            -idx(10):& 0110
                _____________
                       0010(2)
            so 10+2=12 and we update 12 index of tree and continue this process till size of array
        **/
        /**   1      2      3       4       5       6       7       8       9       10    ->index of tree
              1     1-2     3      1-4      5      5-6      7      1-8      9      9-10   ->number of value stored in index i to j
        **/
    }
}
ll query(ll idx,ll sum)
{
    while(idx>0)
    {
        sum+=tree[idx];
        idx-=(idx & -idx);
    }
    return sum;
}
int main()
{
    ll n,q,m,i;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>arr[i];
        update(i,arr[i],n);
    }
    cin>>q;
    while(q--)
    {
        ll x,y;
        cin>>x>>y;
        ll sum1=query(y,0);
        ll sum2=query(x-1,0);
        cout<<sum1-sum2<<endl;
    }
    return 0;
}
