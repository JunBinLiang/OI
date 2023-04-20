
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 2e5 + 10, M = 4e5 + 10;
int h[N], e[M], ne[M], idx = 0;
int dfn[N], low[N], timestamp = 0;
int stk[N], top = 0;
bool in_stk[N];
int id[N], scc_cnt;
int in[N];
bool root[N];

int p[N], p1[N];
int n, m;
struct Edge {
    int u, v, w;
} edges[N];

int find(int pa[], int u) {
    if(u == pa[u]) return u;
    pa[u] = find(pa, pa[u]);
    return pa[u];
}

void add(int a, int b)
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

void reset() {
    for(int i = 0; i <= n; i++) {
        h[i] = -1;
    }
    for(int i = 0; i <= n; i++) {
        dfn[i] = low[i] = 0;
        in[i] = 0;
        id[i] = 0;
        root[i] = false;
        p1[i] = i;
    }
    idx = 0;
    scc_cnt = 0, timestamp = 0;
}

int DEBUG = 5;

bool ok(int mid) {
    for(int i = 0; i < m; i++) {
        if(edges[i].w > mid) {
            add(edges[i].u, edges[i].v);    
        } else {
            add(edges[i].u, edges[i].v);  
            add(edges[i].v, edges[i].u);  
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    
    /*if(mid == DEBUG) {
        cout << "ggId  " << endl;
        for(int i = 1; i <= n; i++) {
            cout << id[i] << "  ";
        }
        cout << endl;
    }*/
    
    
    for(int i = 0; i < m; i++) {
        int id1 = id[edges[i].u], id2 = id[edges[i].v];
        if(id1 != id2) {
            in[id2]++;
        }
    }
    
    /*if(mid == DEBUG) {
        cout << "ggIn  " << endl;
        for(int i = 1; i <= scc_cnt; i++) {
            cout << in[i] << "  ";
        }
        cout << endl;
    }*/
    
    for(int i = 1; i <= scc_cnt; i++) {
        if(in[i] == 0) {
            root[i] = true;
            //if(mid == DEBUG) {
               // cout << "root " << i << endl;
            //}
        }
    }
    
    
    int cnt = 0;
    for(int i = 1; i <= scc_cnt; i++) {
        if(in[i] == 0) {
            cnt++;
        }
    }
    
    /*if(mid == DEBUG) {
        cout << "gg  " << scc_cnt << endl;
        for(int i = 1; i <= scc_cnt; i++) {
            cout << in[i] << "  ";
        }
        cout << endl;
    }*/
    reset();
    return cnt <= 1;
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; i++) p[i] = i, p1[i] = i;
   
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        int r1 = find(p, u), r2 = find(p, v);
        if(r1 != r2) p[r1] = r2;
        edges[i] = {u, v, w};
    }
    
    set<int> s;
    for(int i = 1; i <= n; i++) {
        s.insert(find(p, i));
    }
    if(s.size() > 1) {
        cout << -1 << endl;
        return;
    }

    int l = 0, r = 1e9;
    int res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(mid)) {
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
    memset(h, -1, sizeof h);
    memset(in, 0, sizeof in);
    memset(root, false, sizeof root);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
