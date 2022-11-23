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

const int N = 1e5 + 10;
bool res = false;
vector<pair<int, int>> g[N];
int d1[N];
set<int> se;
int n, a, b;
void dfs1(int pa, int root, int v) {
    if(pa != -1) {
        se.insert(v);
    }
    d1[root] = v;  
    for(pair<int, int>& p : g[root]) {
        int nxt = p.first, w = p.second;
        if(nxt == pa) continue;
        dfs1(root, nxt, v ^ w);
    }
}

void dfs2(int pa, int root, int v) {
    if(root == b) {
        if(v == 0) res = true;
        return;
    } else {
        if(se.find(v) != se.end()) res = true;
    }
    for(pair<int, int>& p : g[root]) {
        int nxt = p.first, w = p.second;
        if(nxt == pa) continue;
        dfs2(root, nxt, v ^ w);
    }
}

void solve() {
    scanf("%d%d%d", &n, &a, &b);
    a--; b--; res = false;
    se.clear();
    for(int i = 0; i < n; i++) g[i].clear(), d1[i] = 0;
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs1(-1, b, 0);
    dfs2(-1, a, 0);

    if(res) cout << "YES" << endl;
    else cout << "NO" << endl;
}  

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
