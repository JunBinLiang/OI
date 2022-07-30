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
   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end



const int N = 4e5 + 10;
ve<ve<int>> a;
map<int, int> f;

int id = 0;
int m;


set<pair<int, int>> sets[N];


void dfs(int u) {

  while(sets[u].size() > 0) {
    pair<int, int> p = *(sets[u].begin());
    if(u >= m) {
      a[p.first][p.second] = 0;
    } else {
      a[u][p.second] = 1;
    }
    sets[u].erase(p);
    //cout << u << " " << p.first << " " << p.second << endl;
    sets[p.first].erase({u, p.second});
    dfs(p.first);
  }
}

void solve() {
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int n; scanf("%d", &n);
    ve<int> b(n);
    for(int j = 0; j < n; j++) {
      scanf("%d", &b[j]);
      f[b[j]]++;
    }
    a.pb(b);
  }

  
  for(auto it = f.begin(); it != f.end(); it++) {
    int x = it -> second;
    if(x % 2 == 1) {
      cout << "NO" << endl;
      return;
    }
  }

  f.clear();
  for(int i = 0; i < m; i++) {
    ve<int>& b = a[i];
    for(int j = 0; j < b.size(); j++) {

      if(f.find(b[j]) == f.end()) {
        f[b[j]] = m + id;
        id++;
      }
      int v = f[b[j]];
      sets[i].insert({v, j});
      sets[v].insert({i, j});
    }
  }
  
  /*for(auto it = f.begin(); it != f.end(); it++) {
      cout << it -> first << " " << it -> second << " " << endl;
  }cout << endl;*/

  for(int i = 0; i < m; i++) {
    dfs(i);
  }


  printf("YES\n");
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < a[i].size(); j++) {
      if(a[i][j] == 0) {
        printf("L");
      } else {
        printf("R");
      }
    }
    printf("\n");
  }


}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
