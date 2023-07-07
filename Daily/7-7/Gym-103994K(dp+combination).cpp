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

const int N = 1e6 + 10, MOD = 1e9 + 7;
int n;
ll dp[N], f[N];
void solve() {
  cin >> n;

  if(n == 1) {
    cout << 1 << " " << 0 << endl;
    return;
  }
  if(n == 2) {
    cout << 2 << " " << 1 << endl;
    return;
  }

  dp[2] = 2;
  dp[3] = 4;
  for(int i = 4; i <= n; i++) {
    dp[i] = dp[i - 1] + (dp[i - 2]) * (i - 1);
    dp[i] %= MOD;
  }
  
  f[2] = 1;
  f[3] = 4;
  for(int i = 4; i <= n; i++) {
      ll ele = i - 1;
      ll tot = (1 + ele) * ele / 2;
      tot %= MOD;
      f[i] = f[i - 1] + (dp[i - 2]) * tot;
      f[i] %= MOD;
      f[i] += (f[i - 2] * ele);
      f[i] %= MOD;
  }

  cout << dp[n] << " " << f[n] << endl;
  
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

