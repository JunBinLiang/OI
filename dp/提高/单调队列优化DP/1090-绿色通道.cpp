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

const int N = 50000 + 50;
int a[N];
int dp[N];
pair<int, int> mono[N];
int n, t;

bool check(int k) {
    k++;
    int res = 2000000000;
    int l = 0, r = - 1;
    for(int i = 0; i < n; i++) dp[i] = 2000000000;
    
    for(int i = 0; i < n; i++) {
        if(i < k) {
            dp[i] = a[i];
        }
        while(r - l + 1 > 0 && i - mono[l].first > k) l++;
        if(r - l + 1 > 0) {
            dp[i] = min(dp[i], a[i] + mono[l].second);
        }
        while(r - l + 1 > 0 && dp[i] < mono[r].second) r--;
        mono[++ r] = {i, dp[i]};
        
    }
    
    for(int i = 0; i < n; i++) {
        if(i + k >= n) res = min(res, dp[i]);
    }

    return res <= t;
}

int main() {
    scanf("%d%d", &n, &t);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int res = -1;
    int l = 0, r = n;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << res << endl;
    return 0;
}
