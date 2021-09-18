#include<bits/stdc++.h>
using namespace std ;

#define ll  long long 
#define ff  first
#define ss second


const int lim = 2e5 + 5 ; 

vector<int> adj[lim] ;
int chainNo, ptr ;
int chainInd[lim], chainHead[lim], posInBase[lim] ;
int depth[lim], pa[lim][20], sbtr[lim] ;
vector< pair<ll, ll> > sa[lim] ;
vector<int> baseArray[lim] ;

void reset(int n){
    for(int i=0; i<=n; i++){
        adj[i].clear() ;
        baseArray[i].clear();
        chainHead[i] = -1 ;
        for(int j=0; j<20; j++) pa[i][j] = -1 ;
    }   
    chainNo = ptr = 0 ;
}

#define left    (iter<<1)+1
#define right   (iter<<1)+2

inline void mrg(int iter,int ch){
    sa[ch][iter].ff = sa[ch][left].ff + sa[ch][right].ff ;
    sa[ch][iter].ss = 0 ;
}

void build_tree(int iter,int lo,int hi,int ch){
    if(lo == hi){
        sa[ch][iter] = {0, 0} ;
        return ;
    }
    int mid = (lo + hi)>>1 ;
    build_tree(left, lo, mid,ch) ;
    build_tree(right, mid+1, hi,ch) ;
    mrg(iter,ch) ;
}


inline void lazy_update(int iter,int lo,int hi,int x,int ch){
    sa[ch][iter].ff += (hi-lo+1) * x ;
    sa[ch][iter].ss += x ;
}

inline void push_down(int iter,int lo,int hi,int mid,int ch){
    lazy_update(left,lo,mid,sa[ch][iter].ss, ch) ;
    lazy_update(right,mid+1,hi,sa[ch][iter].ss, ch) ;
    sa[ch][iter].ss = 0 ;
}

void update_tree(int iter,int lo,int hi,int qi,int qj,int val,int ch){
    if(qi > hi || qj < lo) return ;
    else if(qi<= lo && hi <= qj){
        lazy_update(iter,lo, hi, val,ch) ;
        return ;
    }
    int mid = (lo + hi)>>1 ;
    push_down(iter, lo, hi, mid,ch) ;
    update_tree(left, lo, mid, qi, qj, val,ch) ;
    update_tree(right, mid+1, hi, qi, qj, val,ch) ;
    mrg(iter,ch) ;
}

ll query_tree(int iter,int lo,int hi,int qi,int qj,int ch){
    if(qi > hi || qj < lo) return 0 ;
    else if(qi <= lo && hi <= qj) return sa[ch][iter].ff ;
    int mid = (lo + hi)>>1 ;
    push_down(iter, lo, hi , mid,ch) ;
    ll L = query_tree(left, lo, mid, qi, qj,ch) ;
    ll R = query_tree(right,mid+1, hi, qi, qj,ch) ;
    mrg(iter,ch) ;
    return L+R ;
}

void dfs(int u,int par,int _depth=0){
    pa[u][0] = par , depth[u] = _depth, sbtr[u] = 1 ;

    for(int i=0; i<(int)adj[u].size(); i++){
        int v = adj[u][i] ;
        if(v == par) continue ;
        dfs(v, u, _depth+1) ;
        sbtr[u] += sbtr[v] ;
    }
}

void build_lca(int n){
    for(int j=1; (1<<j)<n; j++){
        for(int i=0; i<n; i++){
            if(pa[i][j-1] != -1)
                pa[i][j] = pa[ pa[i][j-1] ][j-1] ;
        }
    }
}

int get_lca(int u,int v){
    if(depth[u] < depth[v])
        swap(u,v) ;
    int lg = log2(depth[u]) ;
    for(int i=lg; i>=0; i--){
        if(depth[u]-(1<<i) >= depth[v])
            u = pa[u][i] ;
    }
    if(u == v) return u ;
    for(int i=lg; i>=0; i--){
        if(pa[u][i] != -1 && pa[u][i] != pa[v][i]){
            u = pa[u][i] ;
            v = pa[v][i] ;
        }
    }

    return pa[u][0] ;
}

void build_hld(int u,int par){
    if(chainHead[ chainNo ] == -1)
        chainHead[ chainNo ] = u ;
    chainInd[ u ] = chainNo ;
    
    baseArray[chainNo].push_back(0) ;
    posInBase[ u ] = ptr++ ;

    int mx = -1, bg = -1, ncost = -1 ;
    for(int i=0; i<(int)adj[u].size(); i++){
        int v = adj[u][i] ;
        if(v == par) continue ;
        if(sbtr[v] > mx){
            bg = v ;
            mx = sbtr[v] ;
        }
    }

    if(bg != -1) build_hld(bg, u) ;

    for(int i=0; i<(int)adj[u].size(); i++){
        int v = adj[u][i] ;
        if(v == par || v == bg) continue ;
        chainNo++ ;
        ptr = 0 ;
        build_hld(v, u) ;
    }
}

ll query_hld(int u,int v){
    if(u == v) return 0 ;
    int uchain , vchain = chainInd[v] , ans = 0 ;

    while(1){
        uchain = chainInd[u] ;
        if(uchain == vchain){
            if(u == v) break ;
            ll temp = query_tree(0, 0, (int)baseArray[uchain].size()-1, posInBase[v]+1, posInBase[u],uchain) ;
            ans += temp ;
            break ;
        }
        ll temp = query_tree(0, 0, (int)baseArray[uchain].size()-1, posInBase[ chainHead[uchain] ], posInBase[u],uchain) ;
        ans += temp ;
        u = chainHead[uchain] ;
        u = pa[u][0] ;
    }
    return ans ;
}


void update_hld(int u,int v){
    if(u == v) return ;
    int uchain , vchain = chainInd[v] ;

    while(1){
        uchain = chainInd[u] ;
        if(uchain == vchain){
            if(u == v) break ;
            update_tree(0, 0, (int)baseArray[uchain].size()-1, posInBase[v]+1, posInBase[u], 1,uchain) ;
            break ;
        }
        update_tree(0, 0, (int)baseArray[uchain].size()-1, posInBase[ chainHead[uchain] ], posInBase[u], 1,uchain) ;
        u = chainHead[uchain] ;
        u = pa[u][0] ;
    }
}

ll query(int u,int v){
    int lca = get_lca(u, v) ;
    ll ans =  query_hld(u, lca) + query_hld(v, lca) ;
    return ans ;
}
void update(int u,int v){
    int lca = get_lca(u, v) ;
    update_hld(u, lca) ;
    update_hld(v, lca) ;
}





int main(){
    int t ;
    scanf("%d", &t) ;

    while(t--){
        int n ;
        scanf("%d", &n) ;
        reset(n) ;

        vector<pair<ll,ll> > edges(n), ticket(n) ;

        for(int i=0; i<n-1; i++){
            int u, v, x, y ;
            scanf("%d %d %d %d", &u, &v, &x, &y) ;
            u--, v-- ;
            adj[u].push_back( v ) ;
            adj[v].push_back( u ) ;
            edges[i] = {u, v} ;
            ticket[i] = {x, y} ;
        }

        dfs(0, -1) ;
        build_hld(0, -1) ;
        build_lca(n) ;
        for(int i = 0; i <= chainNo; i++){
            sa[i].clear() ;
            sa[i].resize(4*(int)baseArray[i].size() + 10) ;
            build_tree(0, 0, (int)baseArray[i].size()-1, i) ;
        }

        // cerr<< chainHead[0] << endl ;
        for(int i = 1; i < n; i++){
            update(i-1, i) ;
            
        }

        ll ans = 0 ;

        for(int i = 0; i < n-1; i++){
            ll freq = query(edges[i].ff, edges[i].ss) ;
            ans += min(freq*ticket[i].ff, ticket[i].ss) ;
        }

        printf("%lld\n", ans) ;
    }


    
    return 0 ;
}
/*quetion: 

The country of Byteland is divided into N provinces numbered from 1 to N. The provinces are connected via N-1 bidirectional roads in a way that it is possible to reach each province from every other province by using one or more of these roads. Candyman is a cheap tourist who wants to visit every province starting from 1 to N in order. Therefore, he starts from province 1, travels to province 2, from province 2, he travels to province 3, so on and so forth until he reaches province N where his journey ends.

In order to travel between two provinces, he needs to purchase a traveler’s pass ticket. There are two types of tickets for each road: single-pass, and multiple-pass. A single-pass ticket expires each time Candyman uses its corresponding road and he needs to purchase it again if he wishes to use that particular road in the future. A multiple-pass ticket, however, does not expire and can be used as many times as necessary for a particular road.

As you can already imagine, both types of passes have two different costs associated with them. For each road ‘i’, a single-pass ticket costs Si bitcoins, and a multiple-pass ticket costs Mi bitcoins. For this problem, you have to help Candyman to figure out the minimum total cost for finishing his travel routes.

Input
The first line of input contains T (1 <= T <= 10), the number of test cases.

The first line of each test contains an integer N (2 <= N <= 200000), the number of provinces in Byteland. Each of the following N-1 lines contains four integers, U, V, Si, Mi, denoting, there’s a bidirectional road between provinces U and V, and the bitcoin costs of single-pass and multiple-pass tickets for this road respectively. Here, 1 <= U, V <= N and 1 <= Si <= Mi <= 100000.

Output
For each test case, print a line containing the minimum bitcoin amount Candyman needs to finish his journey.

Sample Input
3
4
1 2 3 5
1 3 2 4
2 4 1 3
4
1 4 5 5
3 4 4 7
2 4 2 6
5
1 2 2 3
1 3 2 3
1 4 2 3
1 5 2 3

Sample Output
10
16
11
*/
