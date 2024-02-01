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

struct E {
  int u, v, w;
  bool operator< (E& other) {
      return w > other.w;
  }
};
vector<E> edges;

const int INF = 1e9;

int dx8[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy8[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int dx4[4] = {1, 0, -1, 0};
int dy4[4] = {0, -1, 0, 1};
int topr = 1e9, topc = -1;
int ans[300000 + 10];
int p[1000000 + 5];
set<int> s[1000000 + 5];

vector<string> mat;
vector<vector<int>> dis;
int n, m, q;

bool ingrid(int r, int c) {
  return r >= 0 && r < n && c >= 0 && c < m;
}

int getNode(int i, int j, int x) {
  return (i * m + j) + (x) * (n * m);
}

int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

void merge() {
  for(int i = 0; i < 1000000 + 5; i++) p[i] = i;
  for(auto e : edges) {
    int u = e.u, v = e.v, w = e.w;
    int r1 = find(u), r2 = find(v);
    if(r1 == r2) continue;
    if(s[r1].size() < s[r2].size()) swap(r1, r2);
    p[r2] = r1;
    for(auto i : s[r2]) {
      if(s[r1].find(i) != s[r1].end()) {
        ans[i] = w;
        s[r1].erase(i);
      } else {
        s[r1].insert(i);
      }
    }
  }
}

void bfs() {
  queue<pair<int, int>> q;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == 'v') {
        dis[i][j] = 0;
        q.push({i, j});
      }
    }
  }
  while(q.size() > 0) {
    int sz = q.size();
    for(int i = 0; i < sz; i++) {
      auto p = q.front(); q.pop();
      int r = p.first, c = p.second;
      for(int i = 0; i < 4; i++) {
        int nr = r + dx4[i], nc = c + dy4[i];
        if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        
        if(dis[nr][nc] > dis[r][c] + 1) {
          dis[nr][nc] = 1 + dis[r][c];
          q.push({nr, nc});
        }
      }
    }
  }
}


void solve() {
  cin >> n >> m >> q;
  
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    mat.push_back(s);
    vector<int> d(m, INF);
    dis.push_back(d);
  }

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == '#') {
        topr = i;
        topc = j;
      }
    }
  }

  bfs();

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      for(int x = 0; x < 2; x++) { //since we doing dsu, only 1 direction needed
        int nr = i + dx4[x], nc = j + dy4[x];
        if(!ingrid(nr, nc)) continue;
        if(mat[i][j] == '#' || mat[nr][nc] == '#') continue;
        int di = min(dis[i][j], dis[nr][nc]);
        if(i == topr && j > topc && x == 0) { //top, cross borader
          edges.push_back({getNode(i, j, 0), getNode(nr, nc, 1), di});
          edges.push_back({getNode(i, j, 1), getNode(nr, nc, 0), di});
        } 
        else {
          edges.push_back({getNode(i, j, 0), getNode(nr, nc, 0), di});
          edges.push_back({getNode(i, j, 1), getNode(nr, nc, 1), di});
        }
      }
    }
  }

  sort(edges.begin(), edges.end());
  
  for(int i = 0; i < q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    s[getNode(x, y, 0)].insert(i);
    s[getNode(x, y, 1)].insert(i);
  }

  merge();
  for(int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
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
