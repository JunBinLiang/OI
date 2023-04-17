
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define PII pair<long long, int>


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


const int N = 3e5 + 10, mod = 1e9 + 7;
const int DEL = 1e5;
int dp[N], pre[N];
int get(int l, int r) {
    if(l > r) return 0;
    if(l == 0) return pre[r];
    return (pre[r] - pre[l - 1] + mod) % mod;
}

void solve() {
    int a, b, k, t;
    cin >> a >> b >> k >> t;
    
    memset(dp, 0, sizeof dp);
    dp[DEL] = 1;
    for(int x = 0; x < t; x++) {
        int sum = 0;
        for(int i = 0; i < N; i++) {
            sum += dp[i];
            sum %= mod;
            pre[i] = sum;
        }
        for(int i = 0; i < N; i++) {
            int l = max(0, i - k), r = min(N - 1, i + k);
            dp[i] = get(l, r);
        }
    }
    
    /*for(int i = 0; i < 20; i++) {
        cout << dp[i] << " ";
    } cout << endl;*/
    
    int sum = 0;
    for(int i = 0; i < N; i++) {
        sum += dp[i]; 
        sum %= mod;
        pre[i] = sum;
    }
    
    ll res = 0;
    int d = a - b;
    for(int i = 0; i < N; i++) {
        ll x = dp[i];
        if(d <= 0) { // b > a
            int dd = -d;
            ll y = get(0, i - dd - 1);
            x *= y;
            x %= mod;
        } else {// a > b
            ll y = get(0, min(N - 1, i + d - 1));
            x *= y;
            x %= mod;
        }
        res += x;
        res %= mod;
    }    
    cout << res << endl;
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

