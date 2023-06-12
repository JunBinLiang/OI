
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

int ask(int k, int sign) {
  int res;
  if(sign == 1) {
    cout << "+ " << k << endl;
  } else {
    cout << "- " << k << endl;
  }
  cin >> res;
  return res;
}

void out(int x) {
  cout << "! " << x << endl;
}

void solve() {
  int x;
  cin >> x;
  set<int> s;
  s.insert(x);
  for(int i = 0; i < 999; i++) {
    int v = ask(1, 1);
    if(s.find(v) != s.end()) {
      auto it = s.end();
      it--;
      out(*it);
      return;
    } else {
      s.insert(v);
    }
  }

  int res = 1000;
  for(int i = 0; i < 1000; i++) {
    int v = ask(1000, 1);
    if(s.find(v) != s.end()) { //end cycle
      int l = 0, r = 1000;
      //go back
      v = ask(1000, -1);
      int add = 0;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        int to = ask(mid, 1);
        if(s.find(to) != s.end()) {
          r = mid - 1;
        } else {
          add = mid;
          l = mid + 1;
        }
        ask(mid, -1); //back
      }
      res += add;
      break;
    } else {
      res += 1000;
    }
  }

  out(res);
}

int main()
{   
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
