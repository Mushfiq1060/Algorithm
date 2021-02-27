#include<bits/stdc++.h>
#define ll long long 
using namespace std;

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int arr[n],res[n];
        for(int i=0;i<n;i++)
            scanf("%d",arr+i);
        stack<int>st;
        res[0]=-1;
        for(int i=0;i<n;i++)
        {
            while(!st.empty() && st.top()>arr[i])
                st.pop();
            if(!st.empty()) 
                res[i]=st.top();
            else  
                res[i]=-1;
            st.push(arr[i]);
        }
        for(int i=0;i<n;i++)
            cout<<arr[i]<<" -> "<<res[i]<<endl;
    }
    return 0;
}