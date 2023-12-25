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
#include<fstream>


using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = (1 << 20);
int nxtBit[N];
int a[N], b[N], cnt[N];
ll dp1[N], dp2[20][N];
ll sums[20];
void solve() {
    memset(dp1, 0, sizeof dp1);
    memset(dp2, 0, sizeof dp2);
    memset(cnt, 0, sizeof cnt);
    memset(sums, 0, sizeof sums);
    ll tot = 0;

    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        tot += a[i];
        cnt[a[i]]++;
    }

    for(int mask = 0; mask < N; mask++) {
        int bit = 0;
        while((1 << bit) <= mask) {
            bit++;
        }
        nxtBit[mask] = bit;
    }

    //SOS DP, super set 
    for(int x = 0; x < 20; x++) {
        for(int i = 0; i < n; i++) {
            b[i] = a[i] % (1 << (x + 1));
            dp2[x][a[i]] += b[i];
            sums[x] += b[i];
        }

        for(int i = 0; i < N; i++) {
            dp1[i] = cnt[i];
        }
	    
        for(int i = 0; i < 20; ++i) {
            for(int mask = N - 1; mask >= 0; mask--){
                if(!(mask & (1 << i))) {
                    dp1[mask] += dp1[mask ^ (1 << i)];
                    dp2[x][mask] += dp2[x][mask ^ (1 << i)];
                }
            }
        }

    }

    vector<ll> needs(N); // not sorted
    for(int mask = 1; mask < N; mask++) {
        int bit = 0;
        int x = nxtBit[mask];
        for(int i = x - 1; i >= 0; i--) {
            if(mask & (1 << i)) {
                bit += (1 << i);
            } else {
                continue;
            }

            int lastbit = bit - (1 << i);
            int curCount = n - dp1[bit], lastCount = n - dp1[lastbit];
            //ll nonsum = dp2[i][bit] - dp2[i][lastbit];
            ll nonsum = dp2[i][lastbit] - dp2[i][bit];
            needs[mask] += ((lastCount + 0ll) * (1 << i));
            needs[mask] += (((curCount - lastCount + 0ll) * (1 << i)) - nonsum);
        }
    }

    vector<pair<ll, int>> c;
    vector<int> maxx(N);
    for(int i = 0; i < N; i++) {
        c.push_back({needs[i], i});
    }
    sort(c.begin(), c.end());
    for(int i = 0; i < N; i++) {
        maxx[i] = c[i].second;
        if(i) maxx[i] = max(maxx[i], maxx[i - 1]);
    }

    for(int i = 0; i < m; i++) {
        ll k;
        scanf("%lld", &k);
        if(k >= ((N + 0ll) * n) - tot) {
            k -= (((N + 0ll) * n) - tot);
            printf("%lld\n", (k / n) + N);
        } else {
            int l = 0, r = N - 1;
            int p = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(c[mid].first <= k) {
                    p = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if(p == 0) printf("0\n");
            else printf("%d\n", maxx[p]);
        }
    }
    
}

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}

