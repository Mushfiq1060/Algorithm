#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int cn=0;
struct node
{
    node* next[30];
    bool endmark=false;
    string nodestr="";
    node()
    {
        for(int i=0;i<26;i++)
            next[i]=NULL;
    }
}*root;
void Insert(string str)
{
    int l=str.size();
    node* cur=root;
    for(int i=0;i<l;i++)
    {
        int idx=str[i]-'a';
        if(cur->next[idx]==NULL)
            cur->next[idx]=new node();
        cur=cur->next[idx];
    }
    cur->endmark=true;
    cur->nodestr=str;
}
node* Search(string str)
{
    node* cur=root;
    int l=str.size();
    for(int i=0;i<l;i++)
    {
        int idx=str[i]-'a';
        if(cur->next[idx]==NULL)
            return cur;
        cur=cur->next[idx];
    }
    return cur;
}
void func(node* cur)
{   
    if(cn>=3) ///we print at most 3 suggestion word
        return ;
    if(cur->endmark==true)
    {
        cout<<cur->nodestr<<endl; ///suggestive word
        cn++;
    }
    for(int i=0;i<26;i++)
        if(cur->next[i]!=NULL)
            func(cur->next[i]);
}
int main()
{
    root=new node();
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;
        Insert(str);
    }
    string xd,yd;
    cin>>xd;
    int l=xd.size();
    for(int i=0;i<l;i++)///if we type a word which is searh in dictionary...suggestion after every character type
    {
        yd.push_back(xd[i]);
        node* cur=Search(yd);
        //cout<<"Search -> "<<yd<<" "<<cur<<endl;
        if(cur!=root) ///if we not found search string in trie
            func(cur);
        cn=0;
    }
    return 0;
}
/***
 * 
5
mobile
mouse
moneypot
monitor
mousepad
mouse

m-> mobile,moneypot,monitor
mo-> mobile,moneypot,monitor
mou-> mouse,mousepad
mous-> mouse,mousepad
mouse-> mouse,mousepad
**/