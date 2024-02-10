#include<bits/stdc++.h>
#define ll long long 
using namespace std;
class Hash {
  int n, base = 31, mod = 1000004119;
  string s;
  vector<int> pwr, pref, suff;
  inline int add(int val1, int val2) {
    if(val1 < 0) {
      val1 += mod;
    } 
    if(val2 < 0) {
      val2 += mod;
    } 
    if(val1 + val2 >= mod) {
      return val1 + val2 - mod;
    }
    return val1 + val2;
  }
  inline int mul(int val1, int val2) {
    if(val1 < 0) {
      val1 += mod;
    }
    if(val2 < 0) {
      val2 += mod;
    }
    return ((ll)((ll)val1 * (ll)val2)) % mod;
  }
  inline void buildPowerArray() {
    pwr.push_back(1);
    for (int i = 0; i <= n; i++) {
      pwr.push_back(mul(pwr.back(), base));
    }
  }
  inline void buildPrefixArray() {
    pref.push_back(s[0] - 'a' + 1);
    for (int i = 1; i < n; i++) {
      pref.push_back(add((s[i] - 'a' + 1), mul(pref.back(), base)));
    }
  }
  inline void buildSuffixArray() {
    suff.resize(n + 1, 0);
    for(int i = n - 1; i >= 0; i--) {
      suff[i] = add((s[i] - 'a' + 1), mul(suff[i + 1], base));   
    }
  }

public:
  Hash(string s) {
    this->s = s;
    n = s.size();
    buildPowerArray();
    buildPrefixArray();
    buildSuffixArray();
  }
  int getForwardHash(int l, int r) {
    // by using suffix hash we can get hash value of substring(l -> r)
    return add(suff[l] - mul(suff[r + 1], pwr[r - l + 1]), mod);
  }
  int getReverseHash(int l, int r) {
    // by using prefix hash we can get hash value of substring(r -> l)
    return add(pref[r] - mul((l != 0 ? pref[l - 1] : 0), pwr[r - l + 1]), mod);
  }
};
int main()
{
  string str;
  cin>>str;
  Hash obj = Hash(str);
  int q;
  cin>>q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << obj.getForwardHash(l, r) << endl;
    cout << obj.getReverseHash(l, r) << endl;
  }
  return 0;
}
/*

  str = "yarqs" , p=base

  suffix hash array:

                    s = s*p^0
                   qs = q*p^0 + s*p^1
                  rqs = r*p^0 + q*p^1 + s*p^2
                 arqs = a*p^0 + r*p^1 + q*p^2 + s*p^3
                yarqs = y*p^0 + a*p^1 + r*p^2 + q*p^3 + s*p^4


  prefix hash array: 
                    y =                                 y*p^0
                   ya =                         y*p^1 + a*p^0
                  yar =                 y*p^2 + a*p^1 + r*p^0
                 yarq =         y*p^3 + a*p^2 + r*p^1 + q*p^0
                yarqs = y*p^4 + a*p^3 + r*p^2 + q*p^1 + s*p^0


  gethash(l,r) => suff[l]-(suff[r+1]*pwr[r-l+1]) -> (r>l) -> finding forward hash

  gethash(r,l) => pref[r]-(pref[l-1]*pwr[r-l+1]) -> (r>l) -> finding reverse hash

*/
