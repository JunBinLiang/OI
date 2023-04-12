
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 2e5 + 10, M = 4e5 + 10;
int h[N],h1[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt;
int in[N], dis[N];
int cnt[N];


int n, m;
ll k;
int a[N];
pair<int, int> edge[N];

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}

void solve() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[i] = {u, v};
    }
    
    int l = 0, r = 1e9;
    int res = -1;
    
    
    while(l <= r) {
        int mid = l + (r - l) / 2;
        
        memset(h, -1, sizeof h);
        memset(h1, -1, sizeof h1);
        memset(in, 0, sizeof in);
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        memset(cnt, 0, sizeof cnt);
        memset(dis, 0, sizeof dis);
        idx = 0;
        timestamp = 0;
        scc_cnt = 0;
        
        for(int i = 0; i < m; i++) {
            int u = edge[i].first, v = edge[i].second;
            if(a[u] > mid || a[v] > mid) continue;
            
            add(h, u, v);
        
        }
        
        for(int i = 1; i <= n; i++) {
            if(!dfn[i] && a[i] <= mid) {
                tarjan(i);
            }
        }
        
        
        
        bool cyc = false;
        for(int i = 1; i <= n; i++) {
            if(a[i] > mid) continue;
            int com = id[i];
            cnt[com]++;
            if(cnt[com] > 1) {
                cyc = true;
            }
        }
        
        if(cyc) {
            res = mid;
            r = mid - 1;
            continue;
        }
        
        for(int i = 1; i <= n; i++) {
            for(int j = h[i]; j != -1; j = ne[j]) {
                int id1 = id[i], id2 = id[e[j]];
                if(id1 != id2) {
                   in[id2]++; 
                   add(h1, id1, id2);
                }
            }
        }
        
        bool yes = false;
        queue<int> q;
        for(int i = 1; i <= scc_cnt; i++) {
            if(!in[i]) {
                q.push(i);
                dis[i] = 1;
                if(dis[i] >= k) {
                    yes = true;
                }
            }
        }
        
        while(q.size() > 0) {
            int u = q.front(); q.pop();
            for(int i = h1[u]; ~i; i = ne[i]) {
                int j = e[i];
                dis[j] = max(dis[j], 1 + dis[u]);
                if(dis[j] >= k) {
                    yes = true;
                }
                in[j]--;
                if(!in[j]) {
                    q.push(j);
                }
            }
        }
        
        
        if(yes) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    
    cout << res << endl;
    
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
