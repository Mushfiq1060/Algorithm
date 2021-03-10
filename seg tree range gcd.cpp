/***Segment tree Range value update and Range GCD***/
/**Suppose G=(A1,A2,A3,A4.....,An)
 *         G'=(A1+k,A2+k,A3+k,A4+k......,An+k) -> (1-n) updated with value k
 * now we can write gcd(a,b)=gcd(a,abs(b-a))
 * so we can write G as (A1,A2-A1,A3-A2,......(An-An-1))
 * G'=(A1+k,A2+k-A1-k,A3+k-A2-k,.....An+k-(An-1)-k)
 *   =(A1+k,A2-A1,A3-A2,......,(An-An-1))
 * Here it is clear that we neek to add value with the first value of this segment
 * */

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int lim=5e5+10;
int arr[lim];
struct info
{
    int first,last,lazy,diff;
}tree[4*lim];
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void add(int pos,int left,int right){
    tree[pos].first = tree[left].first;
    tree[pos].last = tree[right].last;

    tree[pos].diff = abs( gcd(tree[left].diff,gcd((tree[right].first-tree[left].last),tree[right].diff)) );
}
void build(int pos,int lo,int hi){
    if(lo==hi){
        tree[pos].first=tree[pos].last=arr[lo];
        return;
    }
    int mid =(lo+hi)/2;
    int left= 2*pos + 1;
    int right = 2*pos+2;
    build(left,lo,mid);
    build(right,mid+1,hi);
    add(pos,left,right);
}
void update(int pos,int lo,int hi,int x,int y,int val){
    if(lo>y or hi<x)return;
    if(lo>=x and hi<=y){
        tree[pos].first+=val;
        tree[pos].last+=val;
        tree[pos].lazy+=val;
        return;
    }
    int mid =(lo+hi)/2;
    int left= 2*pos + 1;
    int right = 2*pos+2;
    update(left,lo,mid,x,y,val);
    update(right,mid+1,hi,x,y,val);
    add(pos,left,right);
    tree[pos].first+=tree[pos].lazy;
    tree[pos].last+=tree[pos].lazy;
}

int query(int pos,int lo,int hi,int x,int y,int carry=0){
    if(lo>y or hi<x) return 0;
    if(lo>=x and hi<=y){
        return gcd(tree[pos].first+carry,tree[pos].diff);
    }
    int mid =(lo+hi)/2;
    int left= 2*pos + 1;
    int right = 2*pos+2;

    int r1 = query(left, lo, mid, x,y,carry+ tree[pos].lazy);
    int r2 = query(right, mid+1,hi,x,y,carry+tree[pos].lazy);
    return gcd(r1,r2);
}
int main()
{
    int n;  
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    build(0,0,n-1);
    int q;
    cin>>q;
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int l,r,v;
            cin>>l>>r>>v;
            update(0,0,n-1,l,r,v);
        }
        else 
        {
            int l,r;
            cin>>l>>r;
            cout<<query(0,0,n-1,l,r)<<endl;
        }
    }
    return 0;
}