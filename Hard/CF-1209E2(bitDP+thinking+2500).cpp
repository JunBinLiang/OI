#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


int n, m;
const int M = 2010, N = 13, INF = 1e9;
int a[N][M];
int dp[N + 1][1 << N];
int sums[1 << 12], best[1 << 12];
int most[1 << 12];
vector<int> subs[1 << 12];


bool comp(vector<int>& v1, vector<int>& v2) {
    return v1.back() > v2.back();
}

void init() {
    for(int i = 0; i < (1 << 12); i++) {
        for(int j = 0; j <= i; j++) {
            if((i & j) == j && (i | j) == i) {
                subs[i].push_back(j);
            }
        }
    }

    for(int i = 1; i < (1 << 12); i++) {
        for(int j = 0; j < 12; j++) {
            if(i & (1 << j)) {
                most[i] = j;
            }
        } 
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    vector<vector<int>> all;
    for(int j = 0; j < m; j++) {
        vector<int> c;
        int mx = a[0][j];
        for(int i = 0; i < n; i++) {
            c.push_back({a[i][j]});
            mx = max(mx, a[i][j]);
        }
        c.push_back(mx);
        all.push_back(c);
    }

    sort(all.begin(), all.end(), comp);
    while(all.size() > n) all.pop_back();

    for(int i = 0; i <= N; i++) {
        for(int j = 0; j < (1 << N); j++) {
            dp[i][j] = -INF;
        }
    }
    

    
    dp[0][0] = 0;
    for(int i = 1; i <= all.size(); i++) {
        auto& p = all[i - 1];
        memset(best, 0, sizeof best);
        for(int shift = 0; shift < n; shift++) {
            sums[0] = 0;
            for(int s = 1; s < (1 << n); s++) {
                int nxt = most[s] + shift;
                if(nxt >= n) nxt -= n;
                sums[s] = sums[s ^ (1 << most[s])] + p[nxt];
                best[s] = max(best[s], sums[s]);
            }

        }
        
        for(int s = 0; s < (1 << n); s++) {
            for(int& sub : subs[s]) {
                dp[i][s] = max(dp[i][s], dp[i - 1][s ^ sub] + best[sub]);
            }
        }
    }

    cout << dp[all.size()][(1 << n) - 1] << endl;
}

int main()
{   

    init();
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
