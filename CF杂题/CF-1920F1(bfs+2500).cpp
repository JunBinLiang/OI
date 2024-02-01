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

const int INF = 1e9;

int dx8[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy8[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int dx4[4] = {0, 0, 1, -1};
int dy4[4] = {1, -1, 0, 0};

vector<string> mat;
vector<vector<int>> dis;
int n, m, q;

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

void bfs1(vector<vector<bool>>& vis, int x, int y, int mid) {
  queue<pair<int, int>> q;
  q.push({x, y});
  vis[x][y] = true;
  while(q.size() > 0) {
    auto p = q.front(); q.pop();
    int r = p.first, c = p.second;
    for(int i = 0; i < 4; i++) {
      int nr = r + dx4[i], nc = c + dy4[i];
      if(nr < 0 || nr >= n || nc < 0 || nc >= m || vis[nr][nc] || dis[nr][nc] < mid || mat[nr][nc] == '#') continue;
      vis[nr][nc] = true;
      q.push({nr, nc});
    }
  }
}

bool bfs2(vector<vector<bool>>& vis, int mid) {
  queue<pair<int, int>> q;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == '#') {
        vis[i][j] = true;
        q.push({i, j});
      }
    }
  }

  /*cout << mid << endl;
  for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
          if(mat[i][j] == '#' || mat[i][j] == 'v')
            cout << mat[i][j] << " ";
          else if(vis[i][j]) cout << "x ";
          else cout << "o ";
      } cout << endl;
  }
  cout << endl << endl;*/

  while(q.size() > 0) {
    auto p = q.front(); q.pop();
    int r = p.first, c = p.second;
    for(int i = 0; i < 8; i++) {
      int nr = r + dx8[i], nc = c + dy8[i];
      if(nr < 0 || nr >= n || nc < 0 || nc >= m || vis[nr][nc]) continue;
      if(nr == 0 || nr == n - 1 || nc == 0 || nc == m - 1) { //border
        return false;
      }
      vis[nr][nc] = true;
      q.push({nr, nc});
    }
  }

  return true;
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

  bfs();

  //for(auto v : dis) cout << v << endl;
  //cout << endl;
  
  while(q--) {
    int x, y;
    cin >> x >> y;
    x--; y--;

    int l = 0, r = dis[x][y];
    int ans = -1;
    while(l <= r) {
      int mid = l + (r - l) / 2;
      vector<vector<bool>> vis(n, vector<bool>(m));
      bfs1(vis, x, y, mid);
      
      if(bfs2(vis, mid)) ans = mid, l = mid + 1;
      else r = mid - 1;
    }
    cout << ans << endl;
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
