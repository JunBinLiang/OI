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


const int N  = 2e5 + 10;
vector<pair<int, int>> g[N];
pair<int, int> edges[N];
int dfn[N], lo[N], a[N];
bool seen[2 * N];
bool b[N];
vector<int> cyc, dist;
int n, t = 0;
ll di = 0;
ll res = 0;

void dfs1(int pa, int root) {
    dfn[root] = lo[root] = ++t;
    seen[root] = true;
    for(pair<int, int>& p : g[root]) {
        int nxt = p.first;
        if(!seen[nxt]) {
            dfs1(root, nxt);
            lo[root] = min(lo[root], lo[nxt]);
            if(dfn[root] < lo[nxt]) { //bridge
                b[p.second] = true;
            }
            lo[root] = min(lo[root], lo[nxt]);
        } else {
            if(nxt != pa) {
                lo[root] = min(lo[root], dfn[nxt]);
            }
        }
    }
}

ll dfs(int pa, int root) {
    vector<ll> line;
    for(pair<int, int>& p : g[root]) {
        int nxt = p.first, idx = p.second;
        if(nxt == pa || !b[idx]) {
            continue;
        }
        ll v = dfs(root, nxt) + a[idx];
        line.push_back(v);
    }    
    sort(line.begin(), line.end());
    reverse(line.begin(), line.end());
    if(line.size() == 0) {
        return 0;
    } else if(line.size() == 1) {
        di = max(di, line[0]);
        return line[0];
    } else {
        di = max(di, line[0] + line[1]);
        return line[0];
    }
}



ll pre[N * 2];
pair<int, ll> mono[N  * 2];
ll get(int l, int r) {
    return pre[r] - pre[l];
}


ll cal(pair<ll, int>& p1, pair<ll, int>& p2) {
    int i = p1.second, j = p2.second;
    if(i == j) {
        return 0;
    }
    return p1.first + p2.first;
}

void linearFind(vector<ll>& points) {
    ll mn = 1000000000000000000ll;
    int n = points.size();
    pre[0] = 0;
    int dIdx = 0;
    for(int i = 1; i < 2 * n; i++) {
        pre[i] = dist[dIdx];
        dIdx++;
        if(dIdx >= dist.size()) dIdx -= dist.size();
        pre[i] += pre[i - 1];
    }
    
    memset(seen, false, sizeof seen);
    
    //pre[y] - pre[x] + dep[y] + dep[x]
    //(pre[y] + dep[y]) + (dep[x] - pre[x])
    priority_queue<pair<ll, int>> pq1;
    priority_queue<pair<ll, int>> pq2;
    for(int i = 0; i < n * 2; i++) {
        pq1.push({pre[i] + points[i % n], i});
        pq2.push({points[i % n] - pre[i], i});
        
        if(i >= n) {
            seen[i - n] = true;
            
            while(pq1.size() > 0 && seen[pq1.top().second]) pq1.pop();
            pair<ll, int> p1 = pq1.top(); pq1.pop();
            while(pq2.size() > 0 && seen[pq1.top().second]) pq1.pop();
            pair<ll, int> p2 = pq1.top();
            
            while(pq2.size() > 0 && seen[pq2.top().second]) pq2.pop();
            pair<ll, int> p3 = pq2.top(); pq2.pop();
            while(pq2.size() > 0 && seen[pq2.top().second]) pq2.pop();
            pair<ll, int> p4 = pq2.top();
            
            ll mx = 0;
            mx = max(mx, cal(p1, p3));
            mx = max(mx, cal(p1, p4));
            mx = max(mx, cal(p2, p3));
            mx = max(mx, cal(p2, p4));
            mn = min(mn, mx);
            
            pq1.push(p1);
            pq2.push(p3);
        }
    }
    res = max(res, mn);
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        edges[i] = {min(u, v), max(u, v)};
        a[i] = w;
        g[u].push_back({v, i});
        g[v].push_back({u, i}); 
    }

    memset(dfn, 0, sizeof dfn);
    memset(lo, 0, sizeof lo);
    memset(seen, false, sizeof seen);
    memset(b, false, sizeof b);
    dfs1(-1, 0);

    //找基环树
    memset(seen, false, sizeof seen);
    for(int i = 0; i < n; i++) {
        if(!b[i]) { // find the cycle
            int u = edges[i].first;
            queue<int> q;
            q.push(u);
            seen[u] = true;
            while(q.size()) {
                int root = q.front(); q.pop();
                cyc.push_back(root);
                bool add = false;
                for(pair<int, int>& p : g[root]) {
                    int nxt = p.first, idx = p.second;
                    if(!b[idx] && !add) {
                        if(!seen[nxt]) {
                            seen[nxt] = true;
                            q.push(nxt);
                            dist.push_back(a[idx]);
                            add = true;
                        } else {
  
                        }
                    }
                }
            }
            break;
        }
    }
    
    for(int i = 0; i < n; i++) {
        int x = min(cyc[0], cyc[cyc.size() - 1]);
        int y = max(cyc[0], cyc[cyc.size() - 1]);
        if(x == edges[i].first && y == edges[i].second) {
            dist.push_back(a[i]);
            break;
        }
    }

    vector<ll> point(cyc.size());
    for(int i = 0; i < cyc.size(); i++) {
        di = 0;
        point[i] = dfs(-1, cyc[i]);
        res = max(res, di);
    }
    
    linearFind(point);
    
    printf("%lld\n", res);
    

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
