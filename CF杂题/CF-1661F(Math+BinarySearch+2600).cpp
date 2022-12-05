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
int a[N];
int n; 
ll k;

ll cost(int i, int c) { //divide into c part
    if(c == 0) return 1000000000000000000ll;
    ll d = a[i + 1] - a[i];
    if(c == 1) {
        return d * d;
    }
    ll x = d / c;
    ll m = d % c;
    ll v = (x * x * (c - m)) + ((x + 1) * (x + 1) * m);
    return v;
}

void solve() {
    scanf("%d", &n);
    a[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%lld", &k);
    
    int res = 2e9;
    ll l = 0, r = 0;
    for(int i = 0; i < n; i++) {
        r = max(r, (a[i + 1] - a[i] + 0ll) * (a[i + 1] - a[i] + 0ll));
    }

    while(l <= r) {
        ll mid = l + (r - l) / 2; //energy
        int cnt = 0;
        ll sum = 0;
        ll minRate = 2e9, all = 0;
        for(int i = 0; i < n; i++) {
            int l1 = 1, r1 = a[i + 1] - a[i];
            int p = -1;
            
            if(mid > cost(i, 1) - cost(i, 2)) { //not install
                sum += ((r1 + 0ll) * (r1 + 0ll));
                cnt++;
                continue;
            }
            
            while(l1 <= r1) {
                int mid1 = l1 + (r1 - l1) / 2;
                ll x = cost(i, mid1) - cost(i, mid1 + 1);
                if(x >= mid) {
                    p = mid1 + 1;
                    l1 = mid1 + 1;
                } else {
                    r1 = mid1 - 1;
                }
            }
            
            ll rate = cost(i, p - 1) - cost(i, p);
            l1 = 1; r1 = p;
            
            int pp = -1;
            while(l1 <= r1) {
                int mid1 = l1 + (r1 - l1) / 2;
                if(cost(i, mid1) - cost(i, mid1 + 1) == rate) {
                    pp = mid1;
                    r1 = mid1 - 1;
                } else {
                    l1 = mid1 + 1;
                }
            }
            
            sum += cost(i, p);
            cnt += p;
            int len = (p - pp);
            if(rate <= minRate) {
                if(rate < minRate) {
                    minRate = rate;
                    all = len;
                } else {
                    minRate = rate;
                    all += len;
                }
            }
        }
        if(sum <= k) {
            l = mid + 1;
            ll remain = k - sum;
            if(minRate != 0) {
                ll cut = remain / minRate;
                cnt -= min(cut, all);
            } else {
                cnt -= all;
            }
            res = min(res, cnt);
        } else {
            r = mid - 1;
        }
    }

    cout << res - (n) << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
