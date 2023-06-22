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

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

const int N = 64;
ll d[N];

void add(ll x) {
    for(int i = N - 1; i >= 0; i--) {
        if(x & (1ll << i)) {
            if(d[i] > 0) x ^= d[i];
            else {
                d[i] = x;
                return;
            }
        }
    }
} 

void solve() {
    memset(d, 0, sizeof d);
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        add(x);
    }
    
    ll res = 0;
    for(int i = N - 1; i >= 0; i--) {
        if((res ^ d[i]) > res) {
            res ^= d[i];
        }
            
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0; 
} 
