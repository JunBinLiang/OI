
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

const int N = 310, mod = 1e9 + 7;
ll f[N], C[N][N];
ll dp[N][N];
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  
  memset(dp, 0, sizeof dp);
  f[0] = 1;
  for(int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= mod;
  }

  C[0][0] = 1;
  for(int i = 1;i < N; i++) {
    C[i][0]=1;
     for(int j = 1;j <= i;j++) {
      C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
    }
  }

  for(int i = 0; i < n; i++) {
    int v = a[i];
    int o = 1;
    for(int j = 2; j * j <= v; j++) {
      if(v % j == 0) {
        int cnt = 0;
        while(v % j == 0) {
          cnt++;
          v /= j;
        }
        if(cnt % 2 == 1) o *= j;
      }
    }
    if(v > 0) o *= v;
    a[i] = o;
  }

  vector<int> b;
  sort(a.begin(), a.end());
  for(int i = 0; i < a.size(); i++) {
    int j = i;
    int cnt = 0;
    while(j < a.size() && a[j] == a[i]) {
      j++;
      cnt++;
    }
    b.push_back(cnt);
    i = j - 1;
  }
  
  //cout << a << endl;
  //cout << b << endl;

  int sum = 0;
  for(int i = 0; i < b.size(); i++) {
    int w = b[i];
    if(i == 0) {
      dp[i][w - 1] = f[w];
      sum += w;
      continue;
    }
    for(int j = 0; j <= w - 1; j++) {
      ll ways = C[w - 1][j] * f[w];
      ways %= mod;
      int chunk = w - j;
      //////////////////////////////////////////////////////////
      for(int done = 0; done <= sum; done++) {
        if(!dp[i - 1][done]) continue;
        int none = sum - 1 - done + 2;

        for(int x = 0; x <= chunk; x++) {
          int y = chunk - x;
          if(done >= x && none >= y) {
            ll t = (C[done][x] * C[none][y]) % mod;
            ll add = dp[i - 1][done] * t;
            add %= mod;
            add *= ways;
            add %= mod;
            dp[i][done - x + j] += add;
            dp[i][done - x + j] %= mod;
            //cout << "yes  " << j << " " << x << " " << chunk << "  |" << done << " " << none << "  " << (done + (j - x)) << endl;
          }
        }
      }
    }
    sum += w;
  }

  cout << dp[b.size() - 1][0] << endl;
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
