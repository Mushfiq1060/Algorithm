#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    int n,w;
    cin>>n>>w;
    int coin[n];
    for(int i=0;i<n;i++)
        cin>>coin[i];
    int dp[n+5][w+5];
    for(int i=0;i<n;i++)
        dp[i][0]=1;
    for(int i=1;i<=w;i++)
    {
        if(i%coin[0]==0)
            dp[0][i]=1;
        else
            dp[0][i]=0;
    }
    for(int i=1;i<n;i++)
        for(int j=1;j<=w;j++)
        {
            if(coin[i]>j)
                dp[i][j]=dp[i-1][j]; ///copy the above cell cause we can't make value using this coin
            else
                dp[i][j]=dp[i-1][j]+dp[i][j-coin[i]]; /// copy above cell + (w(partial)-coin[val] (find this column in this row))
        }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=w;j++)
            cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    cout<<dp[n-1][w]<<endl;
    return 0;
}
///complexity of this code is O(n*w)
