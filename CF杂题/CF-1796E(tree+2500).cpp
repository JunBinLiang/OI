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



const int N = 2e5 + 10, INF = 1e9;
vector<int> g[N];
int dep[N], nodes[N];
int n, k;
int p1 = -1, p2 = -1;

bool dfs(int pa, int u) {
    int min1 = INF, min2 = INF;
    int node1 = 0, node2 = 0;
    nodes[u] = 0;
    
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        if(!dfs(u, nxt)) {
            return false;
        }
        if(dep[nxt] < min1) {
            min2 = min1;
            min1 = dep[nxt];
            node2 = node1;
            node1 = nodes[nxt];
        } else if(dep[nxt] < min2) {
            min2 = dep[nxt];
            node2 = nodes[nxt];
        }
    }
    
    //cout << pa << "  " << u <<"  "<< min1 << " " << min2 << endl;

    if(min1 < k && min2 < k) {
        p1 = node1;
        p2 = node2;
        return false;
    }

    
    if(min1 == INF) { //leafe
        dep[u] = 1;
        nodes[u] = u;
    } else {
        dep[u] = min1 + 1;
        if(dep[u] < k) {
            nodes[u] = node1;
            p1 = node1;
        } else {
            nodes[u] = 0;
        }
    }
    
    
    if(pa == -1) {
        if(dep[u] < k) {
            return false;
        }
    }
    
    return true;
}

bool ok(int mid) {
    k = mid;
    p1 = 1; p2 = 1;
    if(dfs(-1, 1)) return true;
    if(dfs(-1, p1) || dfs(-1, p2)) return true;
    return false;
}

void solve() {
    scanf("%d", &n);
    
    for(int i = 0; i <= n; i++) {
        g[i].clear();
    }
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

   int l = 1, r = n, res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
