#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N = 250, M = 1e5 + 10;
const int INF = 1e9;
int n, m;
ll d[N][N];
int col[N];
bool bi = true;
vector<int> g[N];

void dfs(int u, int c) {
    if(u == 0) return;
    col[u] = c;
    for(int j : g[u]) {
        if(col[j] == -1) {
            dfs(j, c ^ 1);
        } else {
            if(col[u] == col[j]) {
                bi = false;
            }
        }
    }
}


void solve() {
    cin >> n >> m;
    
    memset(col, -1, sizeof col);
    
    for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) d[i][j] = INF;
    for(int i = 1; i <= n; i++) d[i][i] = 0;
    for(int i = 0; i < m; i++) {
        int u, v, o;
        scanf("%d%d%d", &u, &v, &o);
        if(o == 1) {
            d[u][v] = 1;
            d[v][u] = -1;
        } else {
            d[u][v] = d[v][u] = 1;
        }
        g[u].push_back(v);
        g[v].push_back(u);
    }
    

    
    dfs(1, 0);
    
    if(!bi) {
        cout << "NO" << endl;
        return;
    }
    


    
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(d[i][i] < 0) { //neg cycle
            cout << "NO" << endl;
            return;
        }
    }

    int mx = 0, idx = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d[i][j] > mx) {
                mx = d[i][j];
                idx = i;
            }
        }
    }
    
    cout << "YES " << endl;
    cout << mx << endl;
    for(int i = 1; i <= n; i++) {
        cout << d[idx][i] << " ";
    }
    cout << endl;
    
}

int main()
{   solve();
    return 0;
}
