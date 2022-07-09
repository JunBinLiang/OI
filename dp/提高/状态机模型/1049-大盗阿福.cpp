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

int dp[100000 + 5];
void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        dp[i] = x;
        if(i - 2 >= 0) dp[i] = max(dp[i], dp[i - 2] + x);
        if(i) dp[i] = max(dp[i], dp[i - 1]);
    }
    cout << dp[n - 1] << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
