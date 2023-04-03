#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 505;
const ll INF = 1000000000000000000ll;
int n, m, k;
ll c[N][N];
ll dp[N][N][2];
ll f[N][N], g[N][N];
vector<pair<int, int>> le[N][N], up[N][N];
void solve() {
    memset(c, 0, sizeof c);
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    cin >> n >> m >> k;
    for(int i = 0; i < k; i++) {
        int x, y, d, t, e;
        scanf("%d%d%d%d%d", &x, &y, &d, &t, &e);
        pair<int, int> p0 = {x, y}, p1 = {x + d, y - d}, p2 = {x + d, y}, p3 = {x, y + d};
        bool is[4]; memset(is, false, sizeof is);
        if(p0.first + p0.second >= t && (p0.first + p0.second - t) % 4 == 0) {
            is[0] = true;
            c[p0.first][p0.second] += e;
        }

        if(p1.first + p1.second >= t + 1 && (p1.first + p1.second - t - 1) % 4 == 0) {
            is[1] = true;
            c[p1.first][p1.second] += e;
        }

        if(p2.first + p2.second >= t + 2 && (p2.first + p2.second - t - 2) % 4 == 0) {
            is[2] = true;
            c[p2.first][p2.second] += e;
        }

        if(p3.first + p3.second >= t + 3 && (p3.first + p3.second - t - 3) % 4 == 0) {
            is[3] = true;
            c[p3.first][p3.second] += e;
        }
        

        if(is[0] && is[3]) {
            le[p3.first][p3.second].push_back({p0.second, e});
        }

        if(is[1] && is[2]) {
            le[p2.first][p2.second].push_back({p1.second, e});
        }

        if(is[0] && is[2]) {
            up[p2.first][p2.second].push_back({p0.first, e});
        }
    }
    
    /*cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }*/

    /*for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            sort(down[i][j].begin(), down[i][j].end());
            sort(right[i][j].begin(), right[i][j].end());
        }
    }*/

    dp[0][0][0] = dp[0][0][1] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0 && j == 0) continue;
            ll cost1 = 0, cost2 = 0;
            ll t1 = 0, t2 = 0;
            
            for(auto& p : le[i][j]) {
                f[i][p.first] += p.second;
            }
            for(auto& p : up[i][j]) {
                g[p.first][j] += p.second;
            }
            
            for(int k = i - 1; k >= 0; k--) { //up
                cost1 += c[k][j]; 
                cost1 -= g[k][j];
                dp[i][j][0] = min(dp[i][j][0], dp[k][j][1] + cost1);
            }

            for(int k = j - 1; k >= 0; k--) { //left
                cost2 += c[i][k]; 
                cost2 -= f[i][k];
                dp[i][j][1] = min(dp[i][j][1], dp[i][k][0] + cost2);
            }
        }
    }
    
    /*cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << dp[i][j][0] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << dp[i][j][1] << " ";
        }
        cout << endl;
    }*/

    cout << min(dp[n - 1][m - 1][0], dp[n - 1][m - 1][1]) << endl;
    
}

int main()
{
    solve();
    return 0;
}
