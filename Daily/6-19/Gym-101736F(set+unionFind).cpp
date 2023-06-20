
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

const int N = 1e6 + 10;
const ll INF = 100000000000000000ll;
int n, m, newroot;
ll a[N]; char s[4];
ll delta = 0;

int p[N * 2], sz[N * 2], indexMap[N];
ll val[2 * N];
int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

void merge(int x, int y) {
  int r1 = find(x), r2 = find(y);
  if(r1 != r2) {
    p[r2] = r1;
    sz[r1] += sz[r2];
  }
}

set<pair<ll, int>> se;
void solve() {
  scanf("%d%d", &n, &m);
  newroot = n + 1;
  for(int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  
  //[{val, root}]
  for(int i = 1; i <= n; i++) {
    p[i] = i, sz[i] = 1;
    indexMap[i] = i;
    auto it = se.lower_bound({a[i], 0});
    if(it == se.end() || it -> first != a[i]) {
      se.insert({a[i], i});
      val[i] = a[i];
    } else {
      merge(it -> second, i);
    }
  }
  
  /*for(auto it : se) {
      int v = it.first, r = it.second;
      cout << v << "  " << sz[r] << endl;
  }*/

  for(int i = 0; i < m; i++) {
    scanf("%s", s);
    if(s[0] == 'G') { //Grow
      int j, x;
      scanf("%d%d", &j, &x);
      
      int r = find(indexMap[j]);
      sz[r]--;
      if(sz[r] == 0) se.erase({val[r], r});
      
      //open a new root
      a[j] = x + val[r];
      p[newroot] = newroot;
      indexMap[j] = newroot;
      sz[newroot] = 1;
      
      auto it = se.lower_bound({a[j], 0});
      if(it == se.end() || it -> first != a[j]) {
        se.insert({a[j], newroot});
        val[newroot] = a[j];
      } else {
        merge(it -> second, newroot);
      }
      newroot++;
      
    } else if(s[0] == 'C') { //Cut
      int h;
      scanf("%d", &h);
      vector<pair<ll, int>> add;
      while(se.size() > 0) {
        auto it = se.end();
        it--;
        if(it -> first + delta > h) {
          add.push_back(*it);
          se.erase(*it);
        } else {
          break;
        }
      }
      
      ll res = 0;
      if(add.size() > 0) {
        for(int j = 0; j < add.size(); j++) {
          ll x = (add[j].first + delta - h) * sz[add[j].second];
          res += x; 
          merge(add[0].second, add[j].second);
        }
        
        auto it = se.lower_bound({h - delta, 0});
        int r = find(add[0].second);
        if(it == se.end() || it -> first != h - delta) {
            se.insert({h - delta, r});
            val[r] = h - delta;
        } else {
            merge(it -> second, r);
        }
      }
      printf("%lld\n", res);
    } else { //Magic
      int v;
      scanf("%d", &v);
      delta += v;
    }
  }
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
