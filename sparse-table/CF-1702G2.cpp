  


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


template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 200000 + 50;
int n, m;
ve<int> graph[N];
int dis[N];
int f[19][N];
bool is[N];


//11 : 00 - 12 : 03
void dfs(int pa, int root) {
  if(pa != -1) {
    dis[root] = dis[pa] + 1;
    f[0][root] = pa;
  }
  for(int& nxt : graph[root]) {
    if(nxt == pa) continue;
    dfs(root, nxt);
  }
}

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second > p2.second;
}

void jump(int& root, int d) {
  for(int i = 18; i >= 0; i--) {
    if(d & (1 << i)) {
      root = f[i][root];
    }
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    graph[u].pb(v);
    graph[v].pb(u);
  }
  dis[0] = 1;
  memset(f, -1, sizeof(f));
  dfs(-1, 0);

  for(int i = 1; i < 19; i++) {
    for(int j = 0; j < n; j++) {
      int pa = f[i - 1][j];
      if(pa != -1) {
        f[i][j] = f[i - 1][pa];
      }
    }
  }

  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int k; scanf("%d", &k);
    ve<pair<int, int>> a;
    for(int j = 0; j < k; j++) {
      int u;
      scanf("%d", &u);
      u--;
      a.pb({u, dis[u]});
    } 
    sort(a.begin(), a.end(), COMP);
    
    if(a.size() == 1) {
      printf("YES \n");
      continue;
    }
    bool top = false;
    if(a[k - 1].second == a[k - 2].second) {
        top = true;
    }

    for(int j = 0; j < k; j++) {
      is[a[j].first] = true;
    }
    
    int u = a[0].first;
    bool flag = true;
    set<int> s;
    s.insert(u);
    for(int j = 1; j < k; j++) {
      int dif = a[j].second - dis[u];
      dif = abs(dif);
      jump(u, dif);
      if(is[u]) {
        s.insert(u);
      }
    }
    

    //decided 1 line
    ve<pair<int, int>> b;
    for(int j = 0; j < k; j++) {
      if(s.find(a[j].first) == s.end()) {
        b.pb(a[j]);
      }
    }

    if(b.size() > 0) {
        
      int v1 = b[0].first;
      int v2 = a[0].first;
      int to1 = b[0].second - (a[k - 1].second + 1);
      int to2 = a[0].second - (a[k - 1].second + 1);
      
      jump(v1, to1);
      jump(v2, to2);
      if(v1 == v2 && !top) {
        flag = false;
      } else {
        int u = b[0].first;
        for(int j = 1; j < b.size(); j++) {
          if(b[j].second == b[j - 1].second) {
            flag = false;
            break;
          }
          int dif = abs(dis[u] - b[j].second);
          jump(u, dif);
          if(u != b[j].first) {
            flag = false;
          }
        }
      }
    }


    if(flag) {
      printf("YES \n");
    } else {
      printf("NO \n");
    }
    for(int j = 0; j < k; j++) {
      is[a[j].first] = false;
    }
  }
  
}
