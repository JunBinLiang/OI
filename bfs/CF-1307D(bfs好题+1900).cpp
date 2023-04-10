
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector

const int N = 2e5 + 10, INF = 1e9;
vector<int> g[N];
int n, m, k;
vector<int> a;
bool ok[N];
pair<int, int> e[N];
vector<int> d3;
bool comp(int x, int y) {
    return d3[x] < d3[y];
}

void bfs(int S, vector<int>& d) {
    d[S] = 0;
    queue<int> q;
    q.push(S);
    while(q.size() > 0) {
        int u = q.front(); q.pop();
        for(int& nxt : g[u]) {
            if(d[u] + 1 < d[nxt]) {
                d[nxt] = 1 + d[u];
                q.push(nxt);
            }
        }
    }
}

//5:44
void solve() {
    cin >> n >> m >> k;
    memset(ok, false, sizeof ok);
    bool connect = false;

    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        a.push_back(x);
        ok[x] = true;
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        e[i] = {u, v};
        if(ok[u] && ok[v]) {
            connect = true;
        }
    }


    vector<int> d1(n + 1, INF);
    vector<int> d2(n + 1, INF);
    bfs(1, d1); 
    bfs(n, d2);

    if(connect) {
        cout << d1[n] << endl;
        return;
    }


    
    

    /*for(int i = 0; i < k; i++) {
        for(int j = i + 1; j < k; j++) {
            int u = a[i], v = a[j];
            int dis1 = d1[u] + 1 + d2[v];
            int dis2 = d1[v] + 1 + d2[u];
            best = max(best, min(dis1, dis2));
        }
    }*/
    
    for(int i = 0; i < d1.size(); i++) d3.push_back(d1[i]);
    sort(a.begin(), a.end(), comp);
    
    int mx = d1[a[0]];
    int best = 0;
    int res = d1[n];
    for(int i = 1; i < k; i++) {
        int dis = mx + 1 + d2[a[i]];
        best = max(best, dis);
        mx = max(mx, d1[a[i]]);
    }
    res = min(res, best);
    cout << res << endl;

    /*for(int i : d1) cout << i << " ";
    cout << endl;
    
    for(int i : d2) cout << i << " ";
    cout << endl;*/
    
    
}   


int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
