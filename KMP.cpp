/**
 * Time Complexity O(n+m)
 * video: Tusar Roy youtube tutorial
 **/
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
string text,pattern;
int l1,l2,lps[mxn];
int main()
{
    cin>>text>>pattern;
    l1=text.size();
    l2=pattern.size();
    /**build largest proper prefix suffix table on pattern**/
    lps[0]=0;
    int i=1,j=0;
    while(i<l2)
    {
        if(pattern[i]==pattern[j])
            lps[i]=j+1,i++,j++;
        else  
        {
            while(1)
            {
                if(j==0)
                {
                    lps[i]=(pattern[i]==pattern[j]);
                    i++;
                    break;
                }
                j=lps[j-1];
                if(pattern[i]==pattern[j])
                {
                    lps[i]=j+1;
                    i++,j++;
                    break;
                }
            }
        }
    }
    for(int i=0;i<l2;i++)
        cout<<lps[i]<<" ";
    cout<<endl;
    bool found=false;
    i=0,j=0;
    /**Search pattern**/
    while(i<l1)
    {
        if(text[i]==pattern[j])
            i++,j++;
        else  
        {
            while(1)
            {
                if(j==0)
                {
                    i++;
                    break;
                }
                j=lps[j-1];
                if(text[i]==pattern[j])
                {
                    i++,j++;
                    break;
                }
            }
        }
        if(j>=l2)
        {
            found=true;
            break;
        }
    }
    cout<<(found==true?"Pattern found":"Pattern not found")<<endl;
    return 0;
}