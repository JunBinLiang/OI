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
#define pb push_back

const int N = 2e5 + 10;
const int INF = 2e9;
int a[N];
int dp[N][2];
int n;
ll res = 0;
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0, sizeof dp);
    //0: increasing, other decreasing
    //1: decreasing, other increasing
    int last = n;
    for(int i = n; i >= 1; i--) {
        dp[i][0] = INF;
        dp[i][1] = -INF;

        for(int j = i + 1; j <= n; j++) {
            int dec = -INF, inc = INF; //maximize decreasing, minimize increasing
            if(a[j - 1] < a[j]) {
                dec = max(dec, dp[j - 1][0]);
            } else {
                inc = min(inc, dp[j - 1][1]);
            }
            
            if(dp[j - 1][0] > a[j]) {
                inc = min(inc, a[j - 1]);
            }

            if(dp[j - 1][1] < a[j]) {
                dec = max(dec, a[j - 1]);
            }

            if(dp[j][0] == dec && dp[j][1] == inc) {
                break;
            }
            dp[j][0] = dec; dp[j][1] = inc;
            if(dec == -INF && inc == INF) {
                last = j - 1;
                break;
            }
        }
        res += (last - i + 1);
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
