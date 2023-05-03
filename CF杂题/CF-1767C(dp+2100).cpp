
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

int n;
const int N = 210, mod = 998244353, INF = 1e5;
int a[N][N];
int dp[N][N][N];
int r1[N], r2[N], l1[N], l2[N];
//xxxx011111

int dfs(int zero, int one, int i) {
    if(i > n) {
        return 1;
    }

    if(dp[zero][one][i] != -1) {
        return dp[zero][one][i];
    }

    int res = 0;
    //put 0
    if(one == 0) {
        //0000000
        if(r2[i] == -1) {
            res += dfs(i, one, i + 1);
            res %= mod;
        }

    } else {
        //xxxx1000000
        if(r2[i] <= one && l1[i] > one) {
            res += dfs(i, one, i + 1);
            res %= mod;
        }
 
    }
    //put 1
    if(zero == 0) {
        //111111
        if(r2[i] == -1) {
            res += dfs(zero, i, i + 1);
            res %= mod;
        }

    } else {
        //xxx011111
        if(r2[i] <= zero && l1[i] > zero) {
            res += dfs(zero, i, i + 1);
            res %= mod;
        }
    }

    return dp[zero][one][i] = res;
}

void solve() {
    memset(dp, -1, sizeof dp);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    memset(r1, -1, sizeof r1);
    memset(r2, -1, sizeof r2);

    for(int i = 0; i < N; i++) {
        l1[i] = l2[i] = INF;
    }

    for(int r = 1; r <= n; r++) {
        for(int l = r; l >= 1; l--) {
            if(a[l][r] == 1 && r1[r] == -1) {
                r1[r] = l;
            }
            if(a[l][r] == 2 && r2[r] == -1) {
                r2[r] = l;
            }
        }

        for(int l = 1; l <= r; l++) {
            if(a[l][r] == 1 && l1[r] == INF) {
                l1[r] = l;
            }
            if(a[l][r] == 2 && l2[r] == INF) {
                l2[r] = l;
            }
        }
    }

    cout << dfs(0, 0, 1) << endl;
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
