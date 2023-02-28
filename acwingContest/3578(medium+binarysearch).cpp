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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    ll res = a[n / 2];
    ll l = a[n / 2], r = 2e9;
    while(l <= r) {
        ll mid = l + (r - l) / 2;
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] <= mid) {
                cnt++;
            }
        }

        if(cnt < n / 2) {
            r = mid - 1;
        } else {
            ll sum = 0;
            for(int j = n / 2; j < n; j++) {
                if(a[j] < mid) sum += (mid - a[j]);
            }
            if(sum <= k) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    cout << res << endl;
    
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
