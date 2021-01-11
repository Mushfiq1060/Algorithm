// Complexity: O(n log n)
// * * * IMPORTANT: The last character of s must compare less
//       than any other character (for example, do s = s + '\1';
//       before calling this function).
//Output:
// sa   = The suffix array. Contains the n suffixes of s sorted
//        in lexicographical order.
// rank = The inverse of the suffix array. rank[i] = the index
//        of the suffix s[i..n) in the pos array. (In other
//        words, sa[i] = k <==> rank[k] = i).
//        With this array, you can compare two suffixes in O(1):
//        Suffix s[i..n) is smaller than s[j..n) if and
//        only if rank[i] < rank[j].

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5;
int t, _rank[mxn], sa[mxn], lcp[mxn];
bool compare(int i, int j){
    return _rank[i + t] < _rank[j + t];
}
void build(const string &s){
    int n = s.size();
    int bc[256];
    for (int i = 0; i < 256; ++i) bc[i] = 0;
    for (int i = 0; i < n; ++i) ++bc[s[i]];
    for (int i = 1; i < 256; ++i) bc[i] += bc[i-1];
    for (int i = 0; i < n; ++i) sa[--bc[s[i]]] = i;
    for (int i = 0; i < n; ++i) _rank[i] = bc[s[i]];
    for (t = 1; t < n; t <<= 1){
        for (int i = 0, j = 1; j < n; i = j++){
            while (j < n && _rank[sa[j]] == _rank[sa[i]]) j++;
            if (j - i == 1) continue;
            int *start = sa + i, *end = sa + j;
            sort(start, end, compare);
            int first = _rank[*start + t], num = i, k;
            for(; start < end; _rank[*start++] = num){
                k = _rank[*start + t];
                if (k != first and (i > first or k >= j))
                    first = k, num = start - sa;
            }
        }
    }
    // Remove this part if you don't need the LCP
    int size = 0, i, j;
    for(i = 0; i < n; i++) if (_rank[i] > 0) {
        j = sa[_rank[i] - 1];
        while(s[i + size] == s[j + size]) ++size;
        lcp[_rank[i]] = size;
        if (size > 0) --size;
    }
    lcp[0] = 0;
}
int main()
{
    string s;
    cin>>s;
    build(s);
    int n=s.size();
    for(int i=0;i<n;i++)
        cout<<sa[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)
        cout<<lcp[i]<<" ";
    cout<<endl;
    return 0;
}

/***

str -> baabac
suffix of str is :
    
    Suffix  starting-index
------------------------------
    baabac ->     0
    aabac  ->     1
    abac   ->     2
    bac    ->     3
    ac     ->     4
    c      ->     5
After lexicographically sorting suffix : 
 
    Suffix  starting-index(sa array)
------------------------------------
    aabac  ->     1
    abac   ->     2
    ac     ->     4
    baabac ->     0
    bac    ->     3
    c      ->     5
here, suffix array is sa[]={1,2,4,0,3,5}
lcp is stand for longest common prefix of 2 suffix.
lcp[i] means longest common prefix of suffix i and suffix (i-1).
here lcp array is lcp[]={0,1,1,0,2,0}

**/
