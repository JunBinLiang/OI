//https://www.bilibili.com/video/BV1zd4y1T7fX?spm_id_from=333.999.0.0&vd_source=07747202ca6f0fb45ca42a153cb71960
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2005, mod = 998244353;
int T, n, m, k, S[N][N], inv[N];
int qpow(int x, int y = mod - 2) {
  int ret = 1;
  for (; y; y >>= 1, x = (ll)x * x % mod) {
    if (y & 1) ret = (ll)ret * x % mod;
  }
  return ret;
}
void solve() {
  scanf("%d%d%d", &n, &m, &k);
  int ans = 0, res = qpow(m, n), iv = qpow(m);
  for (int i = 1; i <= min(n, k); i++) {
    res = (ll)res * ((m + 1) / 2) % mod * (n - i + 1) % mod * iv % mod;
    ans = (ans + (ll)res * S[k][i]) % mod;
  }
  printf("%d\n", ans);
}
int main() {
  S[1][1] = 1;
  for (int i = 2; i < N; i++) {
    for (int j = 1; j <= i; j++) {
      S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % mod;
    }
  }
  scanf("%d", &T);
  while (T--) solve();
  return 0;
}
