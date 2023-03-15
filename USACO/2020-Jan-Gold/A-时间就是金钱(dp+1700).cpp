#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N = 1010, M = 4010;
int a[N];
int h[N], e[M], w[M], ne[M], idx;
void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
int res = 0;
int n, m, c;
int dp[N][N];

//这复杂度竟然能过。。。
//5:29 - 5 : 50
void solve() {
    scanf("%d%d%d", &n, &m, &c);
    memset(h, -1, sizeof h);
    memset(dp, -1, sizeof dp);
    
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(v, u);
    }
    
    
    
    int res = 0;
    dp[0][1] = 0;
    for(int t = 1; t <= 1000; t++) {
        for(int u = 1; u <= n; u++) {
            for(int i = h[u]; ~i; i = ne[i]) {
                if(dp[t - 1][e[i]] == -1) continue;
                dp[t][u] = max(dp[t][u], dp[t - 1][e[i]] + a[u] - c * (t * t - (t - 1) * (t - 1)));
                if(u == 1) res = max(res, dp[t][u]);
            }
        }
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
