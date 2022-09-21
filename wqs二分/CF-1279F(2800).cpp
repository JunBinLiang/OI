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
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e6 + 10;
int n, k, le;
string s;
int a[N];
int res = N;
int p[N];
int dp[N], f[N];
int check(int cost) {
    memset(dp, 0, sizeof dp);
    f[0] = 0;
    dp[0] = 0;
    for(int i = 1; i <= n; i++) f[i] = n;
    
    for(int i = 1; i <= n; i++) {
        dp[i] = a[i]; 
        dp[i] += dp[i - 1];
        f[i] = f[i - 1];
        
        if(i <= le) {
            if(cost <= dp[i]) {
                if(cost < dp[i]) {
                    dp[i] = cost;
                    f[i] = 1;
                } else {
                    f[i] = min(f[i], 1);
                }
            }   
        }
        else {
            if(dp[i - le] + cost <= dp[i]) {
                if(dp[i - le] + cost < dp[i]) {
                    f[i] = 1 + f[i - le];
                    dp[i] = dp[i - le] + cost;
                } else if(dp[i - le] + cost == dp[i]) {
                    f[i] = min(f[i], 1 + f[i - le]);
                }
            }
        }
    }
    return f[n];
}

void cal() {
    int l = 0, r = n;
    int c = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        int x = check(mid);
        if(x <= k) {
            c = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    check(c);
    res = min(res, dp[n] - k * c);
}

int main() {
    cin >> n >> k >> le;
    cin >> s;
    for(int i = 0; i < n; i++) {
        if(s[i] - 'a' >= 0 && s[i] - 'a' < 26) {
            a[i + 1] = 0;
        } else {
            a[i + 1] = 1;
        }
    }
    
    //flip all 1 to 0
    cal();
    for(int i = 1; i <= n; i++) a[i] ^= 1;
    cal();
    cout << res << endl;
    return 0;
}
