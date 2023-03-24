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
#include <iostream>
   
using ll = long long;
using namespace std;  




int n, m, k;
int bitcnt[300], window[10];
vector<pair<int, int>> a;
const int M = 2020;
int pre[M], dp[M];

void init() {
    for(int i = 0; i < 300; i++) {
        bitcnt[i] = 0;
        for(int j = 0; j < 8; j++) {
            if(i & (1 << j)) bitcnt[i]++;
        }
    }
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        a.push_back({l, i});
        a.push_back({r + 1, -i});
    }

    sort(a.begin(), a.end());
    init();
   
    memset(window, 0, sizeof window);
    memset(pre, -1, sizeof pre);
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    
    
    /*int id = 0;
    for(int i = 0; i < a.size(); i++) {
        int j = i;
        while(j < a.size() && a[j].first == a[i].first) {
            j++;
        }
        f[a[i].first] = id++;
        i = j - 1;
    }*/

    for(int i = 0; i < a.size(); i++) {
        swap(pre, dp);
        int p = a[i].first, w = a[i].second, pos = -1;
        
        int len = 0;
        if(i + 1 < a.size()) len = a[i + 1].first - a[i].first;
        
        if(w > 0) {
            for(int j = 0; j < 10; j++) { //insert the current point in out window
                if(window[j] == 0) {
                    window[j] = w;
                    pos = j;
                    break;
                }
            }

            for(int s = 0; s < (1 << k); s++) {
                dp[s] = pre[s];
                int o = bitcnt[s] % 2;
                if((s & (1 << pos)) > 0) { //take
                    if(pre[s ^ (1 << pos)] != -1) {
                        dp[s] = max(dp[s], len * o + pre[s ^ (1 << pos)]);
                    }
                } else { //previous not take
                    if(dp[s] != -1) dp[s] += len * o;
                }
            }

        } else {
            for(int j = 0; j < 10; j++) { //delete the current point in out window
                if(window[j] == -w) {
                    window[j] = 0;
                    pos = j;
                    break;
                }
            }
            
            for(int s = 0; s < (1 << k); s++) {
                dp[s] = pre[s];
                int o = bitcnt[s] % 2;
                if((s & (1 << pos)) == 0) {
                    if(pre[s ^ (1 << pos)] != -1) {
                        dp[s] = max(dp[s], len * o + pre[s ^ (1 << pos)]);
                    }
                    if(pre[s] != -1) {
                        dp[s] = max(dp[s], pre[s] + len * o);
                    }
                } else {
                    dp[s] = -1;
                }
               
            }
        }
        
        /*cout << p << " " << w << " " << len << endl;
        for(int x = 0; x < 10; x++) cout << dp[x] << "  ";
        cout << endl << endl;*/
    }

    int res = 0;
    for(int i = 0; i < M; i++) {
        res = max(res, dp[i]);
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
