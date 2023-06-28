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
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const unordered_set<T> &a)
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

const int N = 4e5 + 100;
bool vis[N];
int ans[N], last[N];
int n, m, k;
vector<pair<int, int>> interval;
vector<int> g[N];

pair<int, int> get(vector<pair<int, int>>& a, int L, int R) {
  if(L > R) return {-1, -1};
  int p1 = -1, p2 = -1;
  int l = 0, r = a.size() - 1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid].first >= L) {
      p1 = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  l = 0; r = a.size() - 1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid].first <= R) {
      p2 = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  return {p1, p2};
}

void solve() {
  memset(vis, false, sizeof vis);
  memset(ans, 0, sizeof ans);
  memset(last, -1, sizeof last);

  cin >> n >> m >> k;
  vector<int> a(n), b(2 * n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < b.size(); i++) {
    b[i] = a[i % n];
    g[b[i]].push_back(i);
  }

  int i = 0;
  while(!vis[i]) {
    int l = i, r = i + k - 1;
    interval.push_back({l, r});
    vis[i] = true;
    i = r + 1;
    i %= n;
  }

  sort(interval.begin(), interval.end());
  for(int i = 0; i < b.size(); i++) {
    pair<int, int> range = get(interval, max(last[b[i]] + 1, i - k + 1), i);
    
    //cout << "cal : " << i << "     " << max(last[b[i]] + 1, i - k + 1) << "  " << i << endl;
    //cout << range.first << "  " << range.second << endl << endl;

    if(range.first != -1 && range.second != -1 && range.first <= range.second) {
      ans[b[i]] += (range.second - range.first + 1);
      /*if(b[i] == 2) {
          cout << "add  :" << i << "   " << range.second - range.first + 1 << endl;
      }*/
    }
    last[b[i]] = i;
  }

  for(int i = 1; i <= m; i++) {
    printf("%d ", ans[i]);
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

