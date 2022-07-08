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


int a[3005];
int b[3005];
int dp[3005][3005];
int main() {
    int n;
    int res = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < n; i++) {
        int mx = 0;
        for(int j = 0; j < n; j++) {
            if(i) dp[i][j] = dp[i - 1][j];
            
            
            if(b[j] == a[i]) {
                dp[i][j] = max(dp[i][j], 1 + mx);
            }
            if(a[i] > b[j] && i) {
                mx = max(mx, dp[i - 1][j]);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        res = max(res, dp[n - 1][i]);
    }
    
    cout << res << endl;
    return 0;
}
