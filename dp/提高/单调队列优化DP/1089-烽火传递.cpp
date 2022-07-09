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

const int N = 300000;
int a[N], dp[N];
pair<int, int> mono[N];
int l = 0, r = -1;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]); 
        dp[i] = 1000000000;
    }
    
    
    
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
    
    int res = 1000000000;
    for(int i = 0; i < n; i++) {
        if(i + k >= n) res = min(res, dp[i]);
    }
    
    cout << res << endl;
    
    return 0;
}
