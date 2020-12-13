#include<bits/stdc++.h>
#define ll long long 
using namespace std;
struct node
{
    bool endmark;
    node* next[26+5];
    node()
    {
        for(int i=0;i<26;i++)
            next[i]=NULL;
        endmark=false;
    }
}*root;
void insert_in_trie(string str)
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
}
bool Search(string str)
{
    int l=str.size();
    node* cur=root;
    for(int i=0;i<l;i++)
    {
        int idx=str[i]-'a';
        if(cur->next[idx]==NULL)
            return false;
        cur=cur->next[idx];
    }
    return cur->endmark;
}
void del(node* cur)
{
    for(int i=0;i<26;i++)
        if(cur->next[i]!=NULL)
            del(cur->next[i]);
    delete(cur);
}
int main()
{
    root=new node();
    int n;
    cin>>n;
    string s[n+10];
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        insert_in_trie(s[i]); //string insert in trie
    }
    int q;
    cin>>q; //query
    while(q--)
    {
        string str;
        cin>>str;
        if(Search(str)) //search in tree
            cout<<"Found in Dictionary"<<endl;
        else   
            cout<<"Not found in Dictionary"<<endl;
    }
    del(root);
    return 0;
}