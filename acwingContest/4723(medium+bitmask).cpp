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




void solve() {
    int n;
    cin >> n;
    string s = to_string(n);


    ll res = 1000000000000000ll;
    int sz = s.size();
    for(int i = 0; i < (1 << sz); i++) {
        ll v = 0;
        int cnt = 0;
        for(int j = 0; j < sz; j++) {
            if(i & (1 << j)) {
                v = v * 10 + 4;
                cnt++;
            } else {
                v = v * 10 + 7;
            }
        }
        if(v >= n && cnt * 2 == s.size()) res = min(res, v);
    }
    
    if(res == 1000000000000000ll) {
        if(sz % 2 == 0) sz += 2;
        else sz += 1;
        ll v = 0;
        for(int i = 0; i < sz / 2; i++) {
            v = v * 10 + 4;
        }
        
        for(int i = 0; i < sz / 2; i++) {
            v = v * 10 + 7;
        }
        cout << v << endl;
        
    } else {
        cout << res << endl;
    }
}
 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
