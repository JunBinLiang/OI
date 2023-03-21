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
#include <iostream>
   
using ll = long long;
using namespace std;  


const int N = 1e5 + 10, mod = 1e9 + 7, M = 210;
int n, m, k;
int b[20];

ll f1[M], a[M][M];

void mul1() {
    ll temp[M];
    for(int i = 0; i < M; i++) temp[i] = f1[i];
    for(int c = 0; c < M; c++) {
        ll sum = 0;
        for(int r = 0; r < M; r++) {
            sum += (temp[r] * a[r][c]);
            sum %= mod;
        }
        f1[c] = sum;
    }
}

void mul2() {
    ll temp[M][M];
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
            temp[i][j] = a[i][j];
            
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < M; j++) {
            ll sum = 0;
            for(int k = 0; k < M; k++) {
                sum += temp[i][k] * temp[k][j];
                sum %= mod;
            }
            a[i][j] = sum;
        }
    }
}

int shift(int v) {
    return (v << 1) & ((1 << m) - 1); 
}

void solve() {
    cin >> n >> k >> m;

    for(int i = 0; i < 20; i++) {
        b[i] = 0;
        for(int j = 0; j < 5; j++) {
            if(i & (1 << j)) b[i]++;
        }
    }

    memset(f1, 0, sizeof f1);
    memset(a, 0, sizeof a);
    f1[0] = 1;

    /*dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[i][0][0] = 1;
        for(int j = 1; j <= k; j++) {
            for(int st = 0; st < (1 << m); st++) {
                int bcnt = b[st];
                //not take
                int s = shift(st);
                dp[i][j][s] += dp[i - 1][j][st];
                dp[i][j][s] %= mod;
                //take
                dp[i][j][s + 1] += (dp[i - 1][j - 1][st] * (bcnt + 1));
                dp[i][j][s + 1] %= mod;
            }
        }
    }*/
    
    int t = (1 << m);
    a[0][0] = 1;
    for(int j = 1; j <= k; j++) {
        for(int st = 0; st < (1 << m); st++) {
            int s = shift(st);
            int curC = j * t + s;
            int preC = j * t + st;
            a[preC][curC] += 1;
            if(s + 1 < (1 << m)) {
                int bcnt = b[st];
                curC = j * t + (s + 1);
                preC = (j - 1) * t + (st);
                a[preC][curC] += (bcnt + 1);
            }

        }
    }

    
    while(n) {
        if (n & 1) mul1();// res = res * a
        mul2();  // a = a * a
        n >>= 1;
    }

    ll res = 0;
    for(int i = 0; i < (1 << m); i++) {
        int idx = k * t + i;
        res += f1[idx];
        res %= mod;
    } 
    cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
