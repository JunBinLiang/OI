#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector






//5:16 - 5 ： 21
ll cnt[55];
void dfs(int n, ll k) {
    if(n == 1) {
        cout << 1 << endl;
        return;
    }
    ll half = cnt[n - 1];
    
    if(k == half + 1) {
        cout << n << endl;
        return;
    }
    if(k <= half) {
        dfs(n - 1, k);
    } else {
        dfs(n - 1, k - half - 1);
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;
    
    cnt[1] = 1;
    for(int i = 2; i < 55; i++) {
        cnt[i] = cnt[i - 1] * 2 + 1;
    }
    
    dfs(n, k);
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
