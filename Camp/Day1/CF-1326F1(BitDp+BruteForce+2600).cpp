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


int n;
const int N = 16;
int a[N][N];
vector<ll> dp[(1 << 14) + 5][14];
int cnt[1 << N];
ll ans[1 << N];
int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < n; j++) {
            a[i][j] = s[j] - '0';
        }
    }

    memset(cnt, 0, sizeof cnt);
    memset(ans, 0, sizeof ans);
    for(int s = 1; s < (1 << n); s++) {
        for(int j = 0; j < n; j++) {
            if(s & (1 << j)) {
                cnt[s] ++;
            }
        }
    }

    for(int i = 1; i < (1 << n); i++) {
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) dp[i][j] = vector<ll>(1 << (cnt[i] - 1), 0);
        }
    }

    for(int i = 0; i < n; i++) {
        dp[1 << i][i][0] = 1;
    }

    for(int i = 1; i < (1 << n); i++) {
        for(int j = 0; j < n; j++) {
            if(!(i & (1 << j))) continue;
            for(int s = 0; s < dp[i][j].size(); s++) {
                for(int cur = 0; cur < n; cur++) {
                    if((i & (1 << cur))) continue; //already used
                    if(a[j][cur]) {
                        dp[i | (1 << cur)][cur][s | (1 << (cnt[i] - 1))] += dp[i][j][s];
                    } else {
                        dp[i | (1 << cur)][cur][s] += dp[i][j][s];
                    }
                }

                if(i == ((1 << n) - 1)) {
                    ans[s] += dp[i][j][s];
                }
            }
        }
    }
    for(int i = 0; i < (1 << (n - 1)); i++) printf("%lld ", ans[i]);
    return 0;
}
