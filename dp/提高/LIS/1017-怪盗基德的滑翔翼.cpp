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

int a[200];
int dp[201];
void solve() {
    int n;
    cin >> n;
    memset(dp, 0, sizeof(dp));
    int res = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int mx = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(a[i] < a[j]) mx = max(mx, dp[j]);
        }
        dp[i] = 1 + mx;
        res = max(res, dp[i]);
    }
    
    for(int i = n - 1; i >= 0; i--) {
        int mx = 0;
        for(int j = i + 1; j < n; j++) {
            if(a[i] < a[j]) mx = max(mx, dp[j]);
        }
        dp[i] = 1 + mx;
        res = max(res, dp[i]);
    }
    
    cout << res << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
