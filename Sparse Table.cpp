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
    cout<<"Sparse Table : "<<endl;
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

/**
input: 
10
2 6 4 8 4 7 9 15 3 5
10
1 10
2 3
2 2
4 8 
9 9
8 10
2 7
4 7
7 2
5 8

output:
Sparse Table : 
2 2 2 2 
6 4 4 3 
4 4 4 3 
8 4 4 -1 
4 4 4 -1 
7 7 3 -1 
9 9 3 -1 
15 3 -1 -1 
3 3 -1 -1 
5 -1 -1 -1 


2
4
6
4
3
3
4
4
4
4
**/
