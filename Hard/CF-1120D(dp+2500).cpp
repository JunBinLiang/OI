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




const int N = 2e5 + 10;
const ll INF = 100000000000000000ll;
vector<int> g[N];
int a[N];
ll dp[N][2];
bool vis[N][2];
int to[N][2];
int n;

void dfs(int pa, int u) {
    if(g[u].size() == 1 && u != 1) { //leaf
        dp[u][0] = a[u];
        dp[u][1] = 0;
        to[u][0] = u;
        return;
    }

    vector<int> nodes;
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        dfs(u, nxt);
        nodes.push_back(nxt);
    }
    
    vector<ll> l(nodes.size());
    vector<ll> r(nodes.size());
    for(int i = 0; i < nodes.size(); i++) {
        l[i] = dp[nodes[i]][0];
        if(i) l[i] += l[i - 1];
    }

    for(int i = nodes.size() - 1; i >= 0; i--) {
        r[i] = dp[nodes[i]][0];
        if(i + 1 < nodes.size()) r[i] += r[i + 1];
    }

    dp[u][0] = l.back();
    to[u][0] = u;

    for(int i = 0; i < nodes.size(); i++) {
        ll sum = 0;
        if(i) sum += l[i - 1];
        if(i + 1 < nodes.size()) sum += r[i + 1];
        
        if(sum + a[u] + dp[nodes[i]][1] < dp[u][0]) {
            dp[u][0] = sum + a[u] + dp[nodes[i]][1];
            to[u][0] = nodes[i];
        }
        
        if(sum + dp[nodes[i]][1] < dp[u][1]) {
            dp[u][1] = sum + dp[nodes[i]][1];
            to[u][1] = nodes[i];
        }
    }

}

set<int> s;
void go(int pa, int u, int x) {
    if(vis[u][x]) {
        return;
    }
    vis[u][x] = true;
    
    //cout << pa << " " << u << " " << x <<"  " << to[u][x] << endl;

    if(g[u].size() == 1 && u != 1) { //leaf
        if(x == 0) {
           s.insert(u);
        }
        return;
    }
    
    
    
    vector<int> nodes;
    for(int& nxt : g[u]) {
        if(nxt != pa) nodes.push_back(nxt);
    }
    vector<ll> l(nodes.size());
    vector<ll> r(nodes.size());
    for(int i = 0; i < nodes.size(); i++) {
        l[i] = dp[nodes[i]][0];
        if(i) l[i] += l[i - 1];
    }
    for(int i = nodes.size() - 1; i >= 0; i--) {
        r[i] = dp[nodes[i]][0];
        if(i + 1 < nodes.size()) r[i] += r[i + 1];
    }
    
    /////////////////////////////////////////////////////////////

    if(x == 0) {
        if(to[u][x] == u) {
            bool can = false;
            for(int& nxt : nodes) {
                go(u, nxt, 0);
            }

            for(int i = 0; i < nodes.size(); i++) {
                ll sum = 0;
                if(i) sum += l[i - 1];
                if(i + 1 < nodes.size()) sum += r[i + 1];
                
                if(sum + dp[nodes[i]][1] + a[u] == dp[u][0]) {
                    go(u, nodes[i], 1);
                    can = true;
                }
            }
            if(can) s.insert(u);

        } else {
            //fix a route
            int cnt = 0;
            s.insert(u);
            int v = to[u][x];
            for(int i = 0; i < nodes.size(); i++) {
                ll sum = 0;
                if(i) sum += l[i - 1];
                if(i + 1 < nodes.size()) sum += r[i + 1];
                
                if(sum + dp[nodes[i]][1] + a[u] == dp[u][0]) {
                    go(u, nodes[i], 1);
                    cnt++;
                }
            }
            
            for(int& nxt : nodes) {
                if(cnt > 1) {
                    go(u, nxt, 0);
                } else {
                    if(nxt != v) {
                        go(u, nxt, 0);
                    }
                }
            }
            
        }
    } else {
        //allow some route
        int v = to[u][x];
        int cnt = 0;
        for(int i = 0; i < nodes.size(); i++) {
            ll sum = 0;
            if(i) sum += l[i - 1];
            if(i + 1 < nodes.size()) sum += r[i + 1];
            if(sum + dp[nodes[i]][1] == dp[u][1]) {
                go(u, nodes[i], 1);
                cnt++;
            }
        }
        
        for(int& nxt : nodes) {
            if(cnt > 1) {
                go(u, nxt, 0);
            } else {
                if(nxt != v) {
                    go(u, nxt, 0);
                }
            }
        }
    }
}

void solve() {
    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(vis, false, sizeof vis);
    memset(to, -1, sizeof to);
    for(int i = 0; i < N; i++) dp[i][0] = dp[i][1] = INF;

    dfs(-1, 1);
    go(-1, 1, 0);

    
    vector<int> res(s.begin(), s.end());
    cout << dp[1][0] <<" " << res.size() << endl;
    for(int i : res) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
