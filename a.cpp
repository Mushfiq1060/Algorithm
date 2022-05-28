/* 
  Sqrt Decomposition
  Complexity : q*sqrt(n)*log2(sqrt(n))
*/

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int block=550,mxn=3e5+10;
int a[mxn];
vector<int>sq[block];
inline int query(int l,int r,int v)
{
  int leftBlock=l/block,rightBlock=r/block,k=0;
  if(leftBlock==rightBlock){
    for(int i=l;i<=r;i++){
      k+=(a[i]<v);
    }
  } 
  else{
    for(int i=l,end=(leftBlock+1)*block;i<end;i++){
      k+=(a[i]<v);
    }
    for(int i=rightBlock*block;i<=r;i++){
      k+=(a[i]<v);
    }
    for(int i=leftBlock+1;i<rightBlock;i++){
      k+=(lower_bound(sq[i].begin(),sq[i].end(),v)-sq[i].begin());
    }
  }
  return k;
}
inline void update(int idx,int val)
{
  int curBlock=idx/block,pos=0,prev=a[idx];
  while(sq[curBlock][pos]<prev){
    pos++;
  }
  int xd=pos;
  sq[curBlock][pos]=val;
  while(pos<sq[curBlock].size()-1 && sq[curBlock][pos]>sq[curBlock][pos+1]){
    swap(sq[curBlock][pos],sq[curBlock][pos+1]),pos++;
  }
  while(pos>0 && sq[curBlock][pos]<sq[curBlock][pos-1]){
    swap(sq[curBlock][pos],sq[curBlock][pos-1]),pos--;
  }
  a[idx]=val;
}
int main()
{
  int n,q,curBlock=0;
  scanf("%d%d",&n,&q);
  for(int i=0;i<n;i++){
    scanf("%d",&a[i]);
    sq[curBlock].push_back(a[i]);
    if(sq[curBlock].size()==block){
      curBlock++;
    }
  }
  for(int i=0;i<=curBlock;i++){
    sort(sq[i].begin(),sq[i].end());
  }
  while(q--){
    int ty;
    scanf("%d",&ty);
    if(ty==1){
      int l,r,v;
      scanf("%d%d%d",&l,&r,&v); // how many numbers in range l to r less than v
      l--,r--;
      int k=query(l,r,v);
      printf("%d\n",k);
    }
    else{
      int l,r;
      scanf("%d%d",&l,&r); // swap a[l] with a[r]
      l--,r--;
      int u=a[l],v=a[r];
      update(l,v);
      update(r,u);
    }
  }
  return 0;
}