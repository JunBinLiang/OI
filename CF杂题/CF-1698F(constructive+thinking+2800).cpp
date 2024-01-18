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

void rev(V<P<int,int>>& ans, V<int>& a, int l, int r) {
  ans.pb({l + 1, r + 1});
  while(l <= r) {
    swap(a[l], a[r]);
    l++; r--;
  }
}

bool same(P<int, int> p1, P<int, int> p2) {
  return p1.first == p2.first && p1.second == p2.second;
}

P<int, int> find(V<int>& a, int index, int start) {
  int n = a.size();
  V<int> p(n + 1, -1);
  FOR(i, index + 1, n) {
    p[a[i]] = i;
  }
  FOR(i, start, index) {
    if(p[a[i]] != -1) {
      return {i, p[a[i]]};
    }
  }
  return {-1, -1};
}

void solve() {
    int n;
    cin >> n;
    V<int> a(n), b(n);
    V<P<int, int>> ans;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, n) cin >> b[i];

    if(a[0] != b[0] || a.back() != b.back()) {
      cout << "NO" << endl;
      return;
    }
    
    map<P<int, int>, int> f1, f2;
    FOR(i, 0, n - 1) {
      f1[{min(a[i], a[i + 1]), max(a[i], a[i + 1])}]++;
      f2[{min(b[i], b[i + 1]), max(b[i], b[i + 1])}]++;
    }

    if(f1.size() != f2.size()) {
      cout << "NO" << endl;
      return;
    }

    auto it2 = f2.begin();
    for(auto it1 = f1.begin(); it1 != f1.end(); it1++) {
      if(it1 -> second != it2 -> second || !same(it1 -> first, it2 -> first)) {
        cout << "NO" << endl;
        return;
      }
      it2++;
    }


    FOR(i, 1, n) {
      if(a[i] == b[i]) continue;
      bool done = false;
      FOR(j, i + 1, n - 1) {
        if(a[j] == b[i] && a[j + 1] == b[i - 1]) {
          done = true;
          rev(ans, a, i - 1, j + 1);
          break;
        }
      }
      if(done) continue;
      int index = -1;
      FOR(j, i, n - 1) {
        if(a[j] == b[i - 1] && a[j + 1] == b[i]) {
          index = j;
          break;
        }
      }

      P<int, int> p = find(a, index, i);
      if(p.first == -1) {
        p = find(a, index + 1, i);
      }
      rev(ans, a, p.first, p.second);

      //additional reverse
      FOR(j, i + 1, n - 1) {
        if(a[j] == b[i] && a[j + 1] == b[i - 1]) {
          rev(ans, a, i - 1, j + 1);
          break;
        }
      }
      
      //cout << i <<"  " << index << endl;
      //for(int x : a) cout << x << " ";
      //cout << endl << endl;
    }

    /*FOR(i, 0, n) cout << a[i] << " ";
    cout << endl;
    FOR(i, 0, n) cout << b[i] << " ";
    cout << endl;*/
    cout << "YES" << endl;
    cout << ans.size() << endl;
    for(auto p : ans) {
      cout << p.first << " " << p.second << endl;
    }
    
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
