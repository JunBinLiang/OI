#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
 
using ll = long long;
using namespace std;


struct Ans {
  int i, l, r;
};
vector<Ans> res;

const int N = 150;
string s, t;

void out() {
  cout << "YES" << endl;
  cout << res.size() << endl;
  for(auto p : res) {
    cout << p.i + 1 << " " << p.l + 1 << " " << p.r + 1 << endl;
  }
}

void solve() {
  int n;
  cin >> n >> t >> s;
  if(s == t) {
    cout << "YES" << endl;
    cout << 0 << endl;
    return;
  }

  int one = 0;
  for(char c : t) {
    if(c == '1') one++;
  }

  if(one == 0) {
    cout << "NO" << endl;
    return;
  }

  for(int i = 0; i < n; i++) {
    if(t[i] == '1') continue;
    int j = i;
    while(j < n && t[j] == '0') {
      j++;
    }

    if(j < n) {
      res.push_back({j, i, j});
      for(int k = i; k < j; k++) t[k] = '1';
      t[j] = '0';
    } else {
      res.push_back({i - 1, i - 1, j - 1});
      for(int k = i - 1; k < j - 1; k++) {
        t[k] = '1';
      }
      t[j - 1] = '0';
      for(int k = i - 1; k < j - 1; k++) {
        res.push_back({k + 1, k, k + 1});
      }
    }
    i = j - 1;
  }
  
  int p1 = -1, p2 = -1;
  for(int i = 0; i < n; i++) {
      if(t[i] == '0') p1 = i;
  }
  
  for(int i = 0; i < n; i++) {
      if(s[i] == '0') p2 = i;
  }
  
  if(p2 == -1) {
      cout << "NO" << endl;
      return;
  }
  
  if(p1 > p2) {
      for(int i = p1 - 1; i >= p2; i--) {
          res.push_back({i, i, i + 1});
          swap(t[i], t[i + 1]);
      }
  } else if(p1 < p2 && p1 != -1) {
      for(int i = p1; i < p2; i++) {
          res.push_back({i + 1, i, i + 1});
          swap(t[i], t[i + 1]);
      }
  }

  //final
  for(int i = 0; i < n; i++) {
    if(s[i] != t[i]) {
      res.push_back({i, i, i});
      t[i] = s[i];
    }
  }
  out();
  
  
}

int main() {
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
