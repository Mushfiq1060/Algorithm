/** Sparse Table using for Range minimum query**/
/**Time complexity -> O(nlog(n)) for building sparse table and O(1) for per query... n is the size of array**/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main()
{   
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    int k=log2(n);
    int st[n+5][k+5];
    memset(st,-1,sizeof st);

    /**
     * Sparse Table Build
    **/
    for(int i=0;i<n;i++)
        st[i][0]=arr[i];
    for(int j=1;j<=k;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);    
    /**
     * Sparse Table Build End
    **/
   
   /** Print Sparse Table**/
    for(int i=0;i<n;i++,cout<<endl)
        for(int j=0;j<=k;j++)   
            cout<<st[i][j]<<" ";
    cout<<endl<<endl;

    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        l--,r--;
        if(l>r)
            swap(l,r);
        int seg=r-l+1;
        int x=log2(seg),uncoverd=seg-(1<<x);
        int res=min(st[l][x],st[l+uncoverd][x]);
        cout<<res<<endl;
    }
    return 0;
}
