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

//11 : 10 - 11 : 40
const int mod = 1e8 + 7;
const int N = 1010;
ll n, s, a, b;
ll dp[N][N];
ll dfs(int i, int sum) {
    if(i >= n - 1) {
        if(sum % n == 0) {
            return 1;
        }
        return 0;
    }
    
    
    if(dp[i][sum] != -1) {
        return dp[i][sum];
    }
    ll res = 0;
    int remain = (n - i - 1);
    ll x = remain * a;
    ll y = remain * b;
    
    
    ll sum1 = (sum + 0ll) - x;
    ll sum2 = (sum + 0ll) + y;
    sum1 %= n;
    sum1 += n;
    sum1 %= n;
    sum2 %= n;
    sum2 += n;
    sum2 %= n;
    
    res += dfs(i + 1, (int)(sum1));
    res %= mod;
    
    res += dfs(i + 1, (int)(sum2));
    res %= mod;
    
    //cout << i << "  " << sum << " " << res << endl; 
    //cout << x << " " << y << endl;
    //cout << sum1 << " " << sum2 << endl << endl;

    return dp[i][sum] = res;
}

int main() {
    cin >> n >> s >> a >> b;
    memset(dp, -1, sizeof dp);
    int sum = s % n;
    sum += n;
    sum %= n;
    ll res = dfs(0, sum);
    cout << res % mod << endl;
    return 0;
}
