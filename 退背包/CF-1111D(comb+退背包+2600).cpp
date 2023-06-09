
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

const int N = 1e5 + 10, mod = 1e9 + 7;
char s[N];
ll f[N], res[60][60];
int n, m;

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
int cget(char c) {
  int d = c - 'a';
  if(d >= 0 && d < 26) return d;
  return c - 'A' + 26;
}

//https://blog.nowcoder.net/n/66d32a0e17104465b14b784baf978817
//01退背包
void solve() {
  memset(res, 0, sizeof res);

  scanf("%s", s);
  n = strlen(s);
  f[0] = 1;
  for(int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= mod;
  }

  vector<int> cnts(52);
  for(int i = 0; i < n; i++) {
    cnts[cget(s[i])]++;
  }

  ll o1 = f[n / 2];
  ll o2 = (o1 * o1) % mod;
  for(int i = 0; i < 52; i++) {
    if(!cnts[i]) continue;
    int w = cnts[i];
    ll v = modInverse(f[w], mod);
    o2 *= v;
    o2 %= mod;
  }
  

  for(int i = 0; i < 52; i++) {
    if(!cnts[i]) continue;

    //i is not choose
    vector<ll> dp(n / 2 + 1);
    dp[0] = 1;
    for(int j = 0; j < 52; j++) {
      if(!cnts[j]) continue;
      int w = cnts[j];
      for(int k = dp.size() - 1; k >= 0; k--) {
        if(i == j) {  
          
        } else {
          if(k >= w) {
            dp[k] += dp[k - w];
            dp[k] %= mod;
          }
        }
      }
    }
    
    //cout << i << "  " << dp << endl;
    
    res[i][i] = (dp.back() * o2) % mod;
    res[i][i] *= 2;
    res[i][i] %= mod;

    for(int j = i + 1; j < 52; j++) {
      if(!cnts[j]) continue;
      int w = cnts[j];
      vector<ll> ndp(dp.begin(), dp.end());
      //remove
      for(int k = w; k < ndp.size(); k++) {
        ndp[k] -= ndp[k - w];
        ndp[k] %= mod;
        if(ndp[k] < 0) ndp[k] += mod;
      }
      res[i][j] = (ndp.back() * o2) % mod;
      res[i][j] *= 2;
      res[i][j] %= mod;
    }
  }


  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    int c1 = cget(s[u]), c2 = cget(s[v]);
    if(c1 > c2) swap(c1, c2);
    cout << res[c1][c2] << endl;
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
