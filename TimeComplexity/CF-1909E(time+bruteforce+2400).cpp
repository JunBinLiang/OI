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

vector<int> bits[21][4];
set<int> g[25];
void init() {
  int x = 0;
  for(int i = 1; i < 20; i++) {
    int n = i;
    for(int s = 0; s < (1 << n); s++) {
      vector<int> a(n, 0);
      for(int i = 0; i < n; i++) {
        if(s & (1 << i)) {
          int j = i;
          while(j < n) {
            a[j] ^= 1;
            j += (i + 1);
          }
        }
      }
      int cnt = 0;
      for(int i = 0; i < a.size(); i++) {
        if(a[i]) cnt++;
      }
      if(cnt <= 3) {
        bits[n][cnt].push_back(s);
        x++;
      }
    }  
  }

  
}


void solve() {

  for(int i = 0; i < 25; i++) {
    g[i].clear();
  }

  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    if(n < 20) {
      g[u - 1].insert(v - 1);
    }
  }

  if(n < 20) {
    int k = n / 5; // k <= 3
    for(int x = 1; x <= k; x++) {
      for(int s : bits[n][x]) {
        vector<bool> v(n);
        for(int j = 0; j < n; j++) {
          if(s & (1 << j)) {
            v[j] = true;
          }
        }

        bool ok = true;
        vector<int> ans;
        for(int j = 0; j < n && ok; j++) {
          if(v[j]) {
            if(j >= n) ok = false;
            ans.push_back(j);
            for(int nxt : g[j]) {
              if(!v[nxt]) {
                ok = false;
              }
            }
          }
        }
        if(ok) {
          cout << ans.size() << endl;
          for(int x : ans) cout << x + 1 << " ";
          cout << endl;
          return;
        }
      }
    }
    cout << -1 << endl;
  } else {
    printf("%d\n", n);
    for(int i = 1; i <= n; i++) {
      printf("%d ", i);
    }
    printf("\n");
  }
}
    

int main()
{
    int t = 1;
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
