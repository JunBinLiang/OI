
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

const int MOD = 998244353;
const int N = 2010;
int a[N];

ll h = 0;
ll f[N], C[N][N];

void init() {
  f[0] = 1;
  for(int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= MOD;
  }

  C[0][0] = 1;
  for(int i = 1;i < N; i++) {
    C[i][0]=1;
    for(int j = 1;j <= i;j++) {
      C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
    }
  }
}

void solve() {
  init();

  int n;
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    h += a[i];
  }

  h %= MOD;
  
  ll ways = 0;
  for(int i = 1; i <= n; i++) {
    //cycle length
    if(i == 1) {
      ways += f[n - i];
      continue;
    }

    ll o = ((C[n - 1][i - 1]) * f[i]) % MOD;
    o *= f[n - i];
    o %= MOD;

    ways += o;
    ways %= MOD;
  }

  cout << (h * ways) % MOD << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
