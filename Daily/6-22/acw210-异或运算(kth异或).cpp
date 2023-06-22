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
int c = 0;
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
    int n, m;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        add(x);
    }
    
    //re-build base
    for(int i = N - 1; i >= 0; i--) {
        for(int j = i - 1; j >= 0; j--) {
            if(d[i] & (1ll << j)) {
                d[i] ^= d[j];
            }
        }
    }
    
    vector<ll> base;
    for(int i = 0; i < N; i++) {
        if(d[i]) base.push_back(d[i]);
    }
    
    int sz = base.size();
    cout << "Case #" << c << ":" << endl;
    cin >> m;
    for(int i = 0; i < m; i++) {
        ll k;
        cin >> k;
        if(sz < n) { //能异或出0, 线性基只能异或出非0的数
            k--;
        }
        
        if(k >= (1ll << sz)) {
            cout << -1 << endl;
            continue;
        }
        
        ll res = 0;
        for(int j = 0; j < sz; j++) {
          if(k & (1ll << j)) {
              res ^= base[j];
          }
        }
        cout << res << endl;
    }
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        c++;
        solve();
    }
    return 0; 
} 
