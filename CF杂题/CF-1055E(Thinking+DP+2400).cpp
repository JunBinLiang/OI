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

const int N = 1600;
int n, s, m, k;
int a[N];
vector<pair<int, int>> seg;
int in[N][N];
int dp[N][N];
int Nxt1[N];
int mid = 0;

bool check(int mid) {
  for(int i = 0; i < n; i++) {
    int cnt = 0;
    for(int j = i; j < n; j++) {
      if(a[j] <= mid) {
        cnt++;
      }
      in[i][j] = cnt;
    }
  }
  
  memset(dp, 0, sizeof(dp));
  int res = 0;
  /*for(int i = 0; i < n; i++) {
    if(Nxt1[i] != -1) {
      dp[i][1] = in[i][i];
      res = max(res, dp[i][1]);
    }
  }*/
  
  
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j < m; j++) {
      if(i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
      if(Nxt1[i] != -1) {
        dp[Nxt1[i] + 1][j + 1] = max(dp[Nxt1[i] + 1][j + 1], dp[i][j] + in[i][Nxt1[i]]);
      }
    }
  }
  
  /*if(mid == 1) {
      for(int i = 0; i <= n; i++) {
          cout << Nxt1[i] << " ";
      }cout << endl << endl;
      
      for(int i = 0; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
          cout << dp[i][j] << " ";
        } cout << endl;
      }
  }*/

  for(int i = 0; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      res = max(res, dp[i][j]);
    }
  }
  //if(mid == 1) cout << res << endl;
  return res >= k;
}

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

void solve() { 
  cin >> n >> s >> m >> k;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  memset(Nxt1, -1, sizeof(Nxt1));  
  for(int i = 0; i < s; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;
    for(int j = l; j <= r; j++) {
      Nxt1[j] = max(Nxt1[j], r);
    }
  }
  
  
  /*for(int i = 0; i < seg.size(); i++) {
      cout << Nxt1[i] << " ";
  }cout << endl;*/
  

  int l = a[0], r = a[0];
  for(int i = 0; i < n; i++) {
    l = min(l, a[i]);
    r = max(r, a[i]);
  }

  int res = -1;
  while(l <= r) {
    mid = l + (r - l) / 2;
    if(check(mid)) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
