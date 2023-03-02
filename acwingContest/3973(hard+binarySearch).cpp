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






//5:04 - 5 : 09
int n, m;
const int N = 1e5 + 10;
vector<int> a, b;

bool ok(ll mid) {
    int j = 0;
    for(int i = 0; i < m; i++) {
        ll l = (b[i] + 0ll) - mid;
        ll r = (b[i] + 0ll) + mid;
        while(j < a.size() && a[j] >= l && a[j] <= r) j++;
    }
    return j >= a.size();
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }

    for(int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        b.push_back(x);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll res = -1;
    ll l = 0, r = 2e9;
    while(l <= r) {
        ll mid = l + (r - l) / 2;
        if(ok(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
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
