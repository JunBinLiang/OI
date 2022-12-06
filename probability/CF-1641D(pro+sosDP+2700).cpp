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




unsigned long long seed=131;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8)+(seed >> 3);}

bool COMP(vector<int>& p1, vector<int>& p2) {
    return p1[0] < p2[0];
}

const int N = 500000 + 1000;
int n, m;
vector<vector<int>> a;
ll rnd[N];
int dp[1 << 16];
unordered_map<int, int> f;
int id = 0;
const int INF = 2e9 + 10;
int res = INF;
void solve() {
    scanf("%d%d", &n, &m);
    vector<int> c;
    for(int i = 0; i < n; i++) {
        vector<int> b;
        for(int j = 0; j <= m; j++) {
            int x;
            scanf("%d", &x);
            b.push_back(x);
            if(j != m)
                c.push_back(x);
        }
        swap(b[0], b[b.size() - 1]);
        a.push_back(b);
    }

    sort(c.begin(), c.end());
    for(int i = 0; i < c.size(); i++) {
        int j = i;
        while(j < c.size() && c[j] == c[i]) {
            j++;
        }
        f[c[i]] = id++;
        i = j - 1;
    }

    for(int i = 0; i < a.size(); i++) {
        for(int j = 1; j < a[i].size(); j++) {
            a[i][j] = f[a[i][j]];
        }
    }

    for(int t = 0; t < 150; t++) {
        for(int i = 0; i < N; i++) {
            rnd[i] = rand() % 16;
        }
        for(int i = 0; i < (1 << 16); i++) dp[i] = INF;
        for(int i = 0; i < a.size(); i++) {
            int state = 0;
            for(int j = 1; j < a[i].size(); j++) {
                state |= (1 << (rnd[a[i][j]] % 16));
            }
            int w = a[i][0];
            dp[state] = min(dp[state], w);
        }

        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < (1 << 16); j++) {
                dp[j | (1 << i)] = min(dp[j], dp[j | (1 << i)]);
            }
        }

        for(int i = 0; i < (1 << 16); i++) {
            int all = (1 << 16) - 1;
            int other = (all ^ i);
            if(dp[i] != INF && dp[other] != INF) {
                res = min(res, dp[i] + dp[other]);
            } 
        }
    }

    if(res == 2e9 + 10) cout << -1 << endl;
    else cout << res << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
