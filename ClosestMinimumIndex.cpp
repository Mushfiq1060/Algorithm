#include<bits/stdc++.h>
using namespace std;

template <typename T>
class closestMinimumIndex {
  vector<T> arr;
  int n;
  bool checkCondition(int i, int e, int dir) {
    if (dir == 0) {
      return i <= e;
    }
    return i >= e;
  }
public:
  closestMinimumIndex(vector<T> arr) {
    this->arr = arr;
    this->n = arr.size();
  }
  /**
    direction: 0 -> get minimum in left of that index
    direction: 1 -> get minimum in right of that index
  **/
  vector<int> getClosestMinimumIndex(int stIdx, int enIdx, int direction) {
    stack<pair<T, int>> st;
    vector<int> res(n);
    int incr, s, e;
    if (direction == 0) {
      incr = +1;
      s = stIdx;
      e = enIdx;
    }
    else {
      incr = -1;
      s = enIdx;
      e = stIdx;
    }
    for (int i = s; checkCondition(i, e, direction); i += incr) {
      while (!st.empty() && st.top().first > arr[i]) {
        st.pop();
      }
      if (!st.empty()) {
        res[i] = st.top().second;
      } 
      else {
        res[i] = (direction == 0 ? -1 : n);
      }
      st.push({arr[i], i});
    }
    return res;
  }
};

int main() {

  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  closestMinimumIndex<int> obj(arr);
  vector<int> leftMin = obj.getClosestMinimumIndex(0, n - 1, 0);
  for (auto el: leftMin) {
    cout << el << " ";
  }
  cout << endl;
  vector<int> rightMin = obj.getClosestMinimumIndex(0, n - 1, 1);
  for (auto el: rightMin) {
    cout << el << " ";
  }
  cout << endl;
  return 0;
}
