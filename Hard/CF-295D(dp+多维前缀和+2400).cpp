
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 2010, mod = 1e9 + 7;
ll res = 0;
ll dp[N][N], f[N][N];
int n, m;

/*void init() {
    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
      C[i][0]=1;
      for(int j = 1; j <= i;j++) {
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
      }
    }
}*/

void solve() {
    cin >> n >> m;
    memset(dp, 0, sizeof dp);
    memset(f, 0, sizeof f);

    for(int j = 2; j <= m; j++) {
        dp[1][j] = 1;
    }

    for(int i = 2; i <= n; i++) {
        ll add = 0, sum = 0;
        for(int j = 2; j <= m; j++) {
            sum += dp[i - 1][j];
            sum %= mod;
            add += sum;
            add %= mod;
            dp[i][j] = add;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        ll add = 0, sum = 0;
        for(int j = 2; j <= m; j++) {
            ll x = dp[i][j] * (n - i + 1);
            x %= mod;
            x *= (m - j + 1);
            x %= mod;
            res += x;
            res %= mod;
            
            if(i == n) {
            } else {
                sum += dp[i][j];
                sum %= mod;
                add += sum;
                add %= mod;
                if(j > 2) {
                    f[i][j] = (add - dp[i][j] + mod) % mod;
                }
            }
        }
    }
    
    /*for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << res << endl;*/
    
    ll p[N], sums[N];
    memset(p, 0, sizeof p);
    memset(sums, 0, sizeof sums);
    int k = 0;
    for(int i = n; i >= 1; i--) {
        for(int j = 2; j <= m; j++) {
            //no reverse side
            ll ways = (m - j + 1);
            sums[j] += f[k][j];
            sums[j] %= mod;
            p[j] += sums[j];
            p[j] %= mod;
            ll x = (ways * p[j]);
            x %= mod;
            x *= dp[i][j];
            x %= mod;
            
            res += x;
            res %= mod;
            
        }
        k++;
    }

    /*for(int i = 1; i <= n; i++) {
        ll add = 0, sum = 0;
        for(int j = 2; j <= m; j++) {
            ll ways = (m - j + 1);
            if(i == n) {
                
            } else {
                if(j - 1 >= 2) {
                    add += sum;
                    add %= mod;
                    sum += dp[n - i][j - 1];
                    ll x = (ways * dp[i][j]) % mod;
                    x *= add;
                    x %= mod;
                }
            }
        }
    }*/

    cout << res << endl;
}


int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
