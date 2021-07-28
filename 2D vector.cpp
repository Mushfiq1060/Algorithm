#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main()
{
  int n=5,m=3;
  vector<vector<int>>arr(n,vector<int>(m,0)); 
  ///it means there is array with row size n and column size m which is initialize with value 0
  for(int i=0;i<n;i++,cout<<endl)
    for(int j=0;j<m;j++)
      cout<<arr[i][j]<<" ";
  return 0;
}
