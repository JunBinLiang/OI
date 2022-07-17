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
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


bool COMP(pair<int, int>&p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}


int ask1(int root) {
  int res;
  cout << "d " << root << endl;
  cout.flush();
  cin >> res;
  return res;
}

int ask2(int root) {
  int res;
  cout << "s " << root << endl;
  cout.flush();
  cin >> res;
  return res;
}

void out(int res) {
  cout << "! " << res << endl;
  cout.flush();
}

const int N = 200000 + 10, M = 2 * N;
int h[N], e[M], w[M], ne[M], idx;
int dis[N];
bool st[N];
int d;


void add(int a, int b, int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int pa, int root) {
  if(pa != 0) {
    dis[root] = 1 + dis[pa];
  }
  for (int i = h[root]; ~i; i = ne[i]) {
    if (e[i] != pa) {
      dfs(root, e[i]);
    }
  } 
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
      if (e[i] != fa) {
        res += get_size(e[i], u);
      }
    }       
    return res;
}

int get_wc(int fa, int u, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, mx = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(u, j, tot, wc);
        mx = max(mx, t);
        sum += t;
    }
    mx = max(mx, tot - sum);
    if (mx <= tot / 2) wc = u;
    return sum;
}

int cal(int u) {
  get_wc(-1, u, get_size(u, -1), u);
  st[u] = true;  // 删除重心
  
  int dd = ask1(u); 
  if(dd == 0) {
    return u;
  }
  
  for(int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if(dis[j] < dis[u]) { //parent
      int pa = j;
      if(dis[u] > d) { //at bottom
        return cal(pa);
      }
      if(dd + dis[u] == d) {
        int to = ask2(u);
        return cal(to);
      } else {
        return cal(pa);
      }
    } 
  }
  
  int to = ask2(u);
  return cal(to);
}

void solve() {
  int n;
  cin >> n;
  idx = 0;
  memset(h, -1, sizeof(h));
  for(int i = 0; i < n - 1; i ++) {
    int u, v;
    cin >> u >> v;
    add(u, v, 0);
    add(v, u, 0);
  }

  d = ask1(1);
  dis[1] = 0;
  dfs(0, 1);
  int res = cal(1);
  out(res);
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
}
