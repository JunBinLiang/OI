
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

const int N = 5050, mod = 1e9 + 7;
int n, m;
int a[N];
vector<int> g[N];
int p[N][N];
int get(int f[], int l, int r) {
  if(l > r) {
    return 0;
  }
  if(l == 0) return f[r];
  return f[r] - f[l - 1];
}

int find(vector<int>& a, int v) {
  int l = 0, r = a.size() - 1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] == v) {
      return mid;
    } else if(a[mid] > v) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return -1;
}

int lowb(vector<int>& a, int v) {
  int res = -1;
  int l = 0, r = a.size() - 1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] <= v) {
      res = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return res + 1;
}

pair<int, ll> cal(int rev) {
  memset(p, 0, sizeof p);
  if(rev) {
    vector<int> b;
    for(int i = 1; i <= n; i++) b.push_back(a[i]);
    reverse(b.begin(), b.end());
    for(int i = 1; i <= n; i++) a[i] = b[i];
  }

  for(int i = 1; i <= n; i++) {
    p[a[i]][i]++;
    if(!i) continue;
    for(int j = 0; j < N; j++) {
      p[j][i] += p[j][i - 1];
    }
  }

  int mx = -1; ll res = 1;
    for(int i = 0; i <= n; i++) {
      int color = a[i], cnt = 0;
      ll ways = 1;
      int idx = find(g[color], get(p[color], 1, i));
      if(idx == -1 && i != 0) continue;
      
      if(i == 0) {
          color = -1;
      } else {
          //deal with a[i] spesifically
        cnt++;
        ll c = lowb(g[color], get(p[color], i + 1, n));
        if(c != 0) {
            if(c >= idx + 1) {
                c--;
                if(c > 0) {
                    cnt++;
                    ways *= c;
                    ways %= mod;
                }
            } else {
              cnt++;
              ways *= c;
              ways %= mod;
            }
        }
      }
      
      for(int j = 0; j < N; j++) {
        if(j == color || !g[j].size()) continue;
        int lsz = get(p[j], 1, i), rsz = get(p[j], i + 1, n);
        if(g[j].size() == 1) {
          if(g[j][0] <= max(lsz, rsz)) {
            cnt++;
            ll w = 0;
            if(g[j][0] <= lsz) w++;
            if(g[j][0] <= rsz) w++;
            ways *= max(w, 1ll);
            ways %= mod;
          }
        } else {
          int v1 = g[j][0], v2 = g[j][1];
          if(lsz > rsz) swap(lsz, rsz);
          if(v1 <= lsz && v2 <= rsz) {
            int c1 = lowb(g[j], lsz), c2 = lowb(g[j], rsz);
            ll w = (c2 - c1 + 0ll) * c1;
            w += (c1 + 0ll) * (c1 - 1);
            ways *= max(w, 1ll);
            ways %=mod;
            cnt += 2;
          } else if(v1 <= rsz) {
            cnt++;
            ll w = lowb(g[j], rsz) + lowb(g[j], lsz);
            ways *= max(w, 1ll);
            ways %= mod;
          }
        }
      }

      if(cnt > mx) {
        mx = cnt;
        res = ways;
      } else if(cnt == mx) {
        res += ways;
        res %= mod;
      }
      
      //cout << i << "    |" <<  "  " << get(p[color], i + 1, n) << "  " << cnt << " " << ways << endl;
    }
    return {mx, res};
}

void solve() {
    memset(p, 0, sizeof p);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }

    for(int i = 0; i < m; i++) {
      int f, h;
      cin >> f >> h;
      g[f].push_back(h);
    }

    for(int i = 0; i < N; i++) {
      sort(g[i].begin(), g[i].end());
    }

    ///////////////////////////////////////////////

    pair<int, ll> p1 = cal(0);
    //cout << "_________________" << endl;
    cout << p1.first << " " << p1.second << endl;

    
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
