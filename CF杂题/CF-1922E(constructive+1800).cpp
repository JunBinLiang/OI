#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

void check(vector<int>& a) {
  int n = a.size();
  int cnt = 0;
  for(int i = 1; i < (1 << n); i++) {
    vector<int> b;
    for(int j = 0; j < n; j++) {
      if(i & (1 << j)) {
        b.push_back(a[j]);
      }
    }
    bool ok = true;
    for(int j = 1; j < b.size(); j++) {
      if(b[j] <= b[j - 1]) ok = false;
    }
    if(ok) cnt++;
  }
  cout << "check  " << cnt << endl;
}

void solve() {
    ll x;
    cin >> x;
    x--;
    int bit = -1;
    for(int i = 0; i < 62; i++) {
      if(x & (1ll << i)) {
        bit = i;
      }
    }
    
    if(x == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }

    vector<int> ans;
    vector<int> cnt(70);
    for(int i = 1; i <= bit; i++) {
      ans.push_back(i);
    }
    int sz = ans.size();
    ans.push_back(-1000);

    for(int i = 1; i < bit; i++) {
      if(x & (1ll << i)) {
        cnt[sz - i]++;
      }
    }

    if(x % 2 == 1) {
      ans.push_back(-2000);
    }

    //construct the final answer
    vector<int> res;
    int neg = -200;
    for(int i = 0; i < ans.size(); i++) {
      if(cnt[i]) res.push_back(neg--);
      res.push_back(ans[i]);
    }
    //check(res);
    cout << res.size() << endl;
    for(int x : res) cout << x << " ";
    cout << endl;
}
    

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
