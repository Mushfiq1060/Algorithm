#include<bits/stdc++.h>
using namespace std;
int main()
{
    int node,edge,u,v;
    cin>>node>>edge;
    vector<int>_list[node+1];


    ///Create adjacency list
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v;
        _list[u].push_back(v);
        _list[v].push_back(u);
    }
    for(int i=1;i<=node;i++)
    {
        cout<<"Node "<<i<<" : ";
        for(int j=0;j<_list[i].size();j++)
            cout<<_list[i][j]<<" ";
        cout<<endl;
    }


    ///BFS code
    int st,en,level[node+1],parent[node+1];
    memset(level,-1,sizeof level);
    cin>>st>>en;
    queue<int>qu;
    qu.push(st);
    level[st]=0;
    while(!qu.empty())
    {
        int p=qu.front();
        qu.pop();
        for(int i=0;i<_list[p].size();i++)
        {
            int x=_list[p][i];
            if(level[x]==-1)
            {
                level[x]=level[p]+1;
                parent[x]=p;///for path finding
                qu.push(x);
            }
        }
    }
    cout<<level[en]<<endl;


    ///Path printing
    int i;
    cout<<en<<"->";
    for(i=parent[en];i!=st; )
    {
        cout<<i<<"->";
        i=parent[i];
    }
    cout<<i<<endl;
    return 0;
}
/**6 7
1 2
1 4
1 6
2 4
4 3
4 5
3 5**/
