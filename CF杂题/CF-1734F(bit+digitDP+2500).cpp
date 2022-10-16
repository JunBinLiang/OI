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


ll x, n;
ll dp[70][2][2][2];
ll dfs(int i, int small, int add, int cnt) {
    if(i > 62) {
        if((cnt + add) % 2 == 1 && small == 0) {
            return 1;
        }
        return 0;
    }
    if(dp[i][small][add][cnt] != -1) {
        return dp[i][small][add][cnt];
    }
    int b1 = 0;
    if(n & (1ll << i)) b1 = 1;

    int b2 = 0;
    if(x & (1ll << i)) b2 = 1;
    
    //原数
    //对应数
    int x0 = (0 + add + b2) % 2;
    int add0 = 0;
    if(0 + add + b2 >= 2) add0 = 1;
    int cnt0 = (cnt + x0 + 0) % 2;

    int x1 = (1 + add + b2) % 2;
    int add1 = 0;
    if(1 + add + b2 >= 2) add1 = 1;
    int cnt1 = (cnt + x1 + 1) % 2;

    ll res = 0;
    if(small == 0) {
        if(b1 == 0) {
            res += dfs(i + 1, 0, add0, cnt0);
            res += dfs(i + 1, 1, add1, cnt1);
        } else {
            res += dfs(i + 1, 0, add0, cnt0);
            res += dfs(i + 1, 0, add1, cnt1);
        }
    } else {
        if(b1 == 0) {
            res += dfs(i + 1, 1, add0, cnt0);
            res += dfs(i + 1, 1, add1, cnt1);
        } else {
            res += dfs(i + 1, 0, add0, cnt0);
            res += dfs(i + 1, 1, add1, cnt1);
        }
    }
    return dp[i][small][add][cnt] = res;
}

void solve() {
    cin >> x >> n;
    n--;
    memset(dp, -1ll, sizeof dp);
    ll res = dfs(0, 0, 0, 0);
    cout << res << endl;
} 

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
