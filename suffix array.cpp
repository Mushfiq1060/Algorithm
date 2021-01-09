#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e5+10;
char str[mxn];
int s0[(mxn / 3) + 10], sa0[(mxn / 3) + 10];
int n, ar[mxn], sa[mxn], lcp[mxn], bucket[mxn], mem[mxn << 2];

void radixsort(int* source, int* dest, int* val, int n, int lim)
{ 
    int i, s = 0, x;
    memset(bucket, 0, lim << 2);
    for (i = 0; i < n; i++) bucket[val[source[i]]]++;

    for (i = 0; i < lim; i++){
        x = bucket[i];
        bucket[i] = s, s += x;
    }
    for (i = 0; i < n; i++) dest[bucket[val[source[i]]]++] = source[i];
}

void DC3(int* ar, int* sa, int n, int lim, int ptr)
{ 
    int *s12, *sa12;
    int allc = (n / 3) << 1, n0 = (n + 2) / 3;
    int i, j, k, l, c, d, p, t, m, r, counter;
    s12 = &mem[ptr], ptr += (allc + 5), sa12 = &mem[ptr], ptr += (allc + 5);

    c = 0, m = 0, r = n + ((n % 3) == 1);
    for (i = 0; i < r; i++, m++){
        if (m == 3) m = 0;
        if (m) s12[c++] = i;
    }
    s12[c] = sa12[c] = s12[c + 1] = sa12[c + 1] = s12[c + 2] = sa12[c + 2] = 0;
    radixsort(s12, sa12, ar + 2, c, lim + 1);
    radixsort(sa12, s12, ar + 1, c, lim + 1);
    radixsort(s12, sa12, ar, c, lim + 1);

    counter = 0, j = -1;
    for (i = 0; i < c; i++){
        if ((ar[sa12[i]] != j) || (ar[sa12[i] + 1] != k) || (ar[sa12[i] + 2] != l)){
            counter++;
            j = ar[sa12[i]], k = ar[sa12[i] + 1], l = ar[sa12[i] + 2];
        }
        if((sa12[i] % 3) == 1) s12[sa12[i] / 3] = counter;
        else s12[(sa12[i] / 3) + n0] = counter;
    }

    if (counter == c){
        for(i = 0; i < c; i++) sa12[s12[i] - 1] = i;
    }
    else{
        DC3(s12, sa12, c, counter, ptr);
        for (i = 0; i < c; i++) s12[sa12[i]] = i + 1;
    }

    for (i = 0, d = 0; i < c; i++){
        if (sa12[i] < n0) s0[d++] = (sa12[i] * 3);
    }
    radixsort(s0, sa0, ar, d, lim + 1);
    for (k = 0, l = ((n % 3) == 1), r = 0; r < n; r++){
        j = sa0[k];
        i = ((sa12[l] < n0) ? (sa12[l] * 3) + 1 : ((sa12[l] - n0) * 3) + 2);
        if (l == c) sa[r] = sa0[k++];
        else if (k == d) sa[r] = i, l++;
        else{
            if (sa12[l] < n0){
                if ((ar[i] < ar[j]) || (ar[i] == ar[j] && s12[sa12[l] + n0] <= s12[j / 3])) sa[r] = i, l++;
                else sa[r] = j, k++;
            }
            else{
                if ((ar[i] < ar[j]) || (ar[i] == ar[j] && ar[i + 1] < ar[j + 1]) || (ar[i] == ar[j] && ar[i + 1] == ar[j + 1] && s12[sa12[l] - n0 + 1] <= s12[(j /3) + n0]) ) sa[r] = i, l++;
                else sa[r] = j, k++;
            }
        }
    }
}

void LcpArray()
{ 
    int i, j, k;
    for (i = 0; i < n; i++) ar[sa[i]] = i;

    for (k = 0, i = 0; i < n; i++, k?k--:0){
        if (ar[i] == (n - 1)) k = 0;
        else{
            j = sa[ar[i] + 1];
            while(((i + k) < n) && ((j + k) < n) && (str[i + k] == str[j + k])) k++;
        }
        lcp[ar[i]] = k;
    }
}

void Generate()
{
    int i, j, lim = 0;
    for (i = 0; i < n; i++){
        ar[i] = str[i];
        if (ar[i] > lim) lim = ar[i];
    }

    ar[n] = ar[n + 1] = ar[n + 2] = 0;
    DC3(ar, sa, n, lim, 0);
}

int main()
{
    scanf("%s", str);
    n = strlen(str);
    Generate();
    LcpArray();
    for(int i=0;i<n;i++)
        cout<<sa[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)
        cout<<lcp[i]<<" ";
    cout<<endl;
    return 0;
}
/***
 * 
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
lcp[i] means longest common prefix of suffix i and suffix (i+1).

here lcp array is lcp[]={1,1,0,2,0,0}

**/
