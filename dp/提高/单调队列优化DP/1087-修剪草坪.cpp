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

const int N = 100000 + 50;
int a[N];
ll s[N];
ll dp[N];
pair<int, ll> mono[N];
int l = 0, r = -1;


ll get(int left, int right) {
    if(left > right) return 0;
    if(left == 0) return s[right];
    return s[right] - s[left - 1];
}

void solve() {
    int n, k;
    ll res = -1000000000000000000ll;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        s[i] = a[i];
        if(i) s[i] += s[i - 1];
    }
    
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < n; i++) {
        while(r - 1 + 1 > 0 && i - mono[l].first >= k ) l++;
        if(i) dp[i] = dp[i - 1];
        dp[i] = max(dp[i], get(max(0, i - k + 1), i));
        
        if(r - l + 1 > 0) {
            int idx = mono[l].first;
            dp[i] = max(dp[i], mono[l].second - get(i + 1, n - 1));
        }
        //add
        while(r - l + 1 > 0 && (dp[i] + get(i + 2, n - 1)) > mono[r].second) r--;
        mono[++r] = {i + 2, dp[i] + get(i + 2, n - 1)};
    }
    
    for(int i = 0; i < n; i++) {
        res = max(res, dp[i]);
    } 
    
    cout << res << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
}
