#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector


int n, m;
const int N = 110, INF = 1e9;
int levels[N], prices[N], dist[N];
int w[N][N];
bool st[N];

void dij(int l, int r) {
    memset(st, false, sizeof st);
    for(int i = 0; i < N; i++) dist[i] = INF;
    
    dist[0] = 0;
    for(int i = 0; i <= n; i++) {
        int t = -1;
        for(int j = 0; j <= n; j++) {
            if(!st[j] && (t == -1 || dist[t] > dist[j])) { //find the current smallest t
                t = j;
            }
        }
        
        st[t] = true;
        
        for(int j = 0; j <= n; j++) {
            if(dist[j] > dist[t] + w[t][j] && levels[j] >= l && levels[j] <= r) {
                dist[j] = dist[t] + w[t][j];
            }
        }
    }
}

void solve() {
    cin >> m >> n;
    
    for(int i = 0; i < N; i++ ) {
        for(int j = 0; j < N; j++) {
            w[i][j] = INF;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        int k;
        cin >> prices[i] >> levels[i] >> k;
        w[0][i] = prices[i];
        for(int j = 0; j < k; j++) {
            int T, V;
            cin >> T >> V;
            w[T][i] = min(w[T][i], V);
        }
    }
    
    int res = prices[1];
    for(int i = levels[1] - m; i <= levels[1]; i++) {
        dij(i, i + m);
        res = min(res, dist[1]);
    }
    cout << res << endl;
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
