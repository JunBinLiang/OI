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


const int N = 1e3 + 10, mod = 1e9 + 7;
int a[N];
ll dp[N][2];
int n;
//4 : 20
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    memset(dp, 0, sizeof dp);
    dp[0][0] = 0; //first enter
    dp[0][1] = 1; //re-enter
    
    for(int i = 1; i < n; i++) {
        int v = a[i];
        dp[i][0] = (1 + dp[i - 1][0] + dp[i - 1][1]);
        dp[i][0] %= mod;
        ll sum = 0;
        for(int j = v; j <= i - 1; j++) {
            sum += dp[j][1] + 1;
            sum %= mod;
        }
        dp[i][1] = sum + 1;
        
    }
    


    cout << (dp[n - 1][0] + dp[n - 1][1] + 1) % mod << endl;

}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
