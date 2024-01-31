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

void odd(vector<int>& ans, vector<int>& v) {
  int n = v.size();
  vector<int> b(n);
  for(int i = 0; i <= n / 2; i++) {
    b[i * 2] = v[i];
  }

  int j = 1;
  for(int i = n / 2 + 1; i < n; i++) {
    b[j] = v[i];
    j += 2;
  }

  for(int i = 0; i < b.size(); i++) {
    int p = (i - 1 + n) % n;
    ans[b[p]] = b[i];
  }
}

void even(vector<int>& ans, vector<int>& v1, vector<int>& v2) {
  int n = v1.size();
  vector<int> b;
  for(int i = 0; i < n; i++) {
    b.push_back(v1[i]);
    b.push_back(v2[i]);
  }
  
  for(int i = 0; i < b.size(); i++) {
    int p = (i - 1 + b.size()) % b.size();
    ans[b[p]] = b[i];
  }
}

map<int, vector<vector<int>>> f;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for(int i = 1; i <= n; i++) cin >> a[i];

  vector<bool> vis(n + 1);
  for(int i = 1; i <= n; i++) {
    if(vis[i]) continue;
    vector<int> b;
    int u = i;
    while(!vis[u]) {
      b.push_back(u);
      vis[u] = true;
      u = a[u];
    }
    f[b.size()].push_back(b);
  }
  
  vector<int> ans(n + 1);
  for(auto it = f.begin(); it != f.end(); it++) {
      auto sz = it -> first;
      auto paths = it -> second;
      if(sz == 1) {
        for(auto v : paths) {
            ans[v[0]] = v[0];
        }
        continue;
      }
      
      if(sz % 2 == 1) {
        for(auto v : paths) {
          odd(ans, v);
        }
      } else {
        if(paths.size() % 2 == 1) {
          cout << -1 << endl;
          return;
        }

        for(int i = 0; i < paths.size(); i += 2) {
          even(ans, paths[i], paths[i + 1]);
        }
      }
  }
  
  for(int i = 1; i <= n; i++) cout << ans[i] << " ";
  cout << endl;
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
