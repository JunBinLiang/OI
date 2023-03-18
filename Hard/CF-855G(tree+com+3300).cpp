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
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N  = 1e5 + 10;
vector<int> g[N];
int sz[N], dep[N], fa[N];
ll ban[N];
int cnt[N], p[N];
int n, m;
ll tot = 0;

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void dfs(int pa, int u) {
    fa[u] = pa;
    sz[u] = 1;
    if(pa != -1) dep[u] = dep[pa] + 1;
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        dfs(u, nxt);
        sz[u] += sz[nxt];
        ban[u] =  ban[u] + (sz[nxt] + 0ll) * (sz[nxt]);
    }

    tot += ((sz[u] - 1ll) * (n - sz[u]) * 2);
    ll sum = 0;
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        tot += (sum * sz[nxt] * 2);
        sum += sz[nxt];
    }

    ll t = n - sz[u];
    ban[u] = ban[u] + t * t;
}

ll cal(int u) {
    return (cnt[u] + 0ll) * (cnt[u] - 1) * (cnt[u] - 2);
}

void merge(int x, int y) {
    //single
    tot = tot - ((n - cnt[x] + 0ll) * (n - cnt[x]) * cnt[x] - (ban[x] * cnt[x]));
    tot = tot - ((n - cnt[y] + 0ll) * (n - cnt[y]) * cnt[y] - (ban[y] * cnt[y]));
    //double
    //乘2：外面不能是w
    tot = tot - (n - cnt[x]) * cnt[x] * (cnt[x] - 1) * 2;  
    tot = tot - (n - cnt[y]) * cnt[y] * (cnt[y] - 1) * 2; 
    //triple
    tot -= cal(x); tot -= cal(y);
    
    //union find merge
    p[x] = y; cnt[y] += cnt[x];
    ban[y] = ban[y] - (sz[x] + 0ll) * sz[x] + ban[x] - (n - sz[x] +0ll) * (n - sz[x]);

    //triple
    tot += cal(y);
    //double
    tot = tot + (n - cnt[y]) * cnt[y] * (cnt[y] - 1) * 2;
    //single
    tot = tot + ((n - cnt[y] + 0ll) * (n - cnt[y]) * cnt[y] - (ban[y] * cnt[y]));

}

void solve() {
    memset(ban, 0, sizeof ban);
    
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 0; i < N; i++) p[i] = i, cnt[i] = 1  ;
    dep[1] = 0;

    dfs(-1, 1);

    scanf("%d", &m);
    cout << tot << endl;
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        int r1 = find(u), r2 = find(v);
        while(r1 != r2) {
            if(dep[r1] < dep[r2]) swap(r1, r2);
            int r3 = find(fa[r1]);
            merge(r1, r3); 
            r1 = r3;
        }
        cout << tot << endl;
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
