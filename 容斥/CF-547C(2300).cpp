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

//2:50 
const int N = 2e5 + 10, M = 5e5 + 10;
int n, m;
int a[N], b[N][64], cnt[M], bitcnt[100];
bool vis[N], is[M];
vector<int> g[M];

void solve() {
    memset(vis, false, sizeof vis);
    memset(is, false, sizeof is);
    memset(cnt, 0, sizeof cnt);

    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(int i = 2; i < M; i++) {
        if(is[i]) continue;
        for(int j = i; j < M; j += i) {
            is[j] = true;
            g[j].push_back(i);
        }
    }

    for(int i = 0; i < n; i++) {
        int sz = g[a[i]].size();
        for(int st = 1; st < (1 << sz); st++) {
            int v = 1;
            for(int j = 0; j < sz; j++) {
                if(st & (1 << j)) {
                    v *= g[a[i]][j];
                }
            }
            b[i][st] = v;
        }
    }

    memset(bitcnt, 0, sizeof bitcnt);
    for(int st = 0; st < 100; st++) {
        for(int j = 0; j < 8; j++) {
            if(st & (1 << j)) {
                bitcnt[st]++;
            }
        }
    }

    ll res = 0;
    int tot = 0;
    for(int i = 0; i < m; i++) {
        int idx;
        scanf("%d", &idx);
        idx--;
        int v = a[idx];
        int sz = g[v].size();

        if(vis[idx]) { //delete
            vis[idx] = false;
            tot--;
            
            for(int st = 1; st < (1 << sz); st++) {
                if(bitcnt[st] % 2 == 1) {
                    cnt[b[idx][st]]--;
                } else {
                    cnt[b[idx][st]]++;
                }
            }

            ll sum = 0;
            for(int st = 1; st < (1 << sz); st++) {
                int p = b[idx][st];
                sum += cnt[p];
            }
            res -= (tot - sum);

        } else { //add
            vis[idx] = true; 
            
            ll sum = 0;
            for(int st = 1; st < (1 << sz); st++) {
                int p = b[idx][st];
                sum += cnt[p];
            }
  
            
            res += (tot - sum);
            tot++;
            for(int st = 1; st < (1 << sz); st++) {
                if(bitcnt[st] % 2 == 1) {
                    cnt[b[idx][st]]++;
                } else {
                    cnt[b[idx][st]]--;
                }
            }

        }
        
        printf("%lld\n", res);
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
