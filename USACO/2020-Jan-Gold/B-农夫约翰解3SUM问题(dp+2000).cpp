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



//2:14
int n, m;
const int N = 5050;
int a[N];
ll dp[N][N];
const int SZ = 4e6 + 1000, B = 2e6;
int cnt[SZ];

void solve() {
    scanf("%d%d", &n, &m);
    memset(dp, 0, sizeof dp);
    memset(cnt, 0, sizeof cnt);
    
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = i - 1; j >= 1; j--) {
            int v = a[j];
            dp[j][i] = dp[j][i - 1] + dp[j + 1][i] - dp[j + 1][i - 1];
            v = (-v) + B;
            dp[j][i] += cnt[v];
            cnt[a[i] + a[j] + B]++; 
        }
        
        for(int j = i - 1; j >= 1; j--) {
             cnt[a[i] + a[j] + B]--; 
        }
    }
    
  
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", dp[l][r]);
    }
    
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}



