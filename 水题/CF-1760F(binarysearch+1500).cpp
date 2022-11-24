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
void solve() {
    int n, d;
    ll c;
    cin >> n >> c >> d;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    
    ll s = 0;
    for(int i = 0; i < min(d, n); i++) {
        s += a[i];
    }

    if(s >= c) {
        cout << "Infinity" << endl;
        return;
    }

    if((d + 0ll) * a[0] < c) {
        cout << "Impossible" << endl;
        return;
    }

    int l = 1, r = d;
    int res = 0;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        s = 0;
        for(int i = 0; i < d; i++) {
            int turn = i % (mid + 1);
            if(turn < n) {
                s += a[turn];
            }
        }

        if(s >= c) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << res << endl;
}  

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
