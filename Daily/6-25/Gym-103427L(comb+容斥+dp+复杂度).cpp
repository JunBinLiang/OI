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

const int N = 4010, mod = 998244353;
int n, m;
vector<int> g[N];
ll dp[N][N][2];
ll temp[N][2];
ll f[N], sz[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}  
  
ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

ll C(int n,int m) {
  return f[n] * fpow(f[n - m], mod - 2) % mod * fpow (f[m], mod - 2) % mod;
}

//O(n ^ 2)
void dfs(int pa, int u) {
  sz[u] = 1;
  dp[u][0][0] = 1;

  for(int v : g[u]) {
    if(v == pa) continue;
    dfs(u, v);
    memset(temp, 0, sizeof temp);
    for(int i = 0; i <= sz[u] / 2; i++) {
      for(int j = 0; j <= sz[v] / 2; j++) {
        temp[i + j][0] += (dp[u][i][0] * dp[v][j][0]);
        temp[i + j][0] += (dp[u][i][0] * dp[v][j][1]);
        temp[i + j][0] %= mod;

        temp[i + j][1] += (dp[u][i][1] * dp[v][j][0]);
        temp[i + j][1] += (dp[u][i][1] * dp[v][j][1]);
        temp[i + j][1] %= mod;

        temp[i + j + 1][1] += (dp[u][i][0] * dp[v][j][0]);
        temp[i + j + 1][1] %= mod;
      }
    }
    sz[u] += sz[v];
    for(int i = 0; i <= sz[u] / 2; i++) {
      dp[u][i][0] = temp[i][0];
      dp[u][i][1] = temp[i][1];
    }
  }
}

void solve() {
  cin >> n;
  m = n * 2;
  for(int i = 0; i < m - 1; i ++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  f[0] = 1;
  for(int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= mod;
  }

  ll res = ((C(m, n) * f[n]) % mod * modInverse(fpow(2, n), mod)) % mod;
  memset(dp, 0, sizeof dp);

  dfs(-1, 1);

  int mul = 1;
  for(int k = 1; k <= n; k++) {
    mul *= -1;
    int point = m - 2 * k;
    ll w = (dp[1][k][0] + dp[1][k][1]) % mod;
    int p = m - 2 * k;
    ll x = ((C(p, p / 2) * f[p / 2] % mod) * modInverse(fpow(2, p / 2), mod)) % mod;
    x *= w;
    x %= mod;
    x *= mul;
    res += x;
    res %= mod;
    if(res < 0) res += mod;
  }
  cout << res << endl;
}

int main()
{
    int t = 1;
    while(t--) {
      solve();
    }
    return 0;
}
