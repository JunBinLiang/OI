#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;
using ll = long long;



namespace FWT {
    const int mod = 1e9 + 7;
    const int N = 1e6;
    int n, m;
    int a[N], b[N];

    ll quick(ll x, ll p)
    {
        ll ret = 1;
        while(p)
        {
            if(p & 1) ret = ret * x % mod;
            x = x * x % mod;
            p >>= 1; 
        }
        return ret;
    }

    inline void mul() {
        for (int i = 0; i < n; i++) {
            a[i] = (a[i] + 0ll) * b[i] % mod;
            if(a[i] < 0) a[i] += mod;
        }
    }

    void XOR(int a[], int x) {
        for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
            for (int i = 0; i < n; i += o)
                for (int j = 0; j < k; j++) {
                    a[i + j] += a[i + j + k],
                    a[i + j] %= mod;
                    if(a[i + j] < 0) a[i + j] += mod;
                    
                    
                    a[i + j + k] = a[i + j] - a[i + j + k] - a[i + j + k];
                    a[i + j + k] %= mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                    
                    a[i + j] = ((a[i + j] + 0ll) * x) % mod, a[i + j + k] =  (a[i + j + k] + 0ll) * x % mod;
                    
                    if(a[i + j] < 0) a[i + j] += mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                }
    }

    void assign(int v1[]) {
        for(int i = 0; i < n; i++) {
            a[i] = v1[i];
        }
        XOR(a, 1);
    }

    void solve(int v2[]) {
        for(int i = 0; i < n; i++) {
            b[i] = v2[i];
        }
        XOR(b, 1);
        mul();
    }

    void end() {
        XOR(a, quick(2ll, mod - 2));
    }
}

namespace FWTCHECK {
    const int mod = 998244353;
    const int N = 1e6;
    int n, m;
    int a[N], b[N];

    ll quick(ll x, ll p)
    {
        ll ret = 1;
        while(p)
        {
            if(p & 1) ret = ret * x % mod;
            x = x * x % mod;
            p >>= 1; 
        }
        return ret;
    }

    inline void mul() {
        for (int i = 0; i < n; i++) {
            a[i] = (a[i] + 0ll) * b[i] % mod;
            if(a[i] < 0) a[i] += mod;
        }
    }

    void XOR(int a[], int x) {
        for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
            for (int i = 0; i < n; i += o)
                for (int j = 0; j < k; j++) {
                    a[i + j] += a[i + j + k],
                    a[i + j] %= mod;
                    if(a[i + j] < 0) a[i + j] += mod;
                    
                    
                    a[i + j + k] = a[i + j] - a[i + j + k] - a[i + j + k];
                    a[i + j + k] %= mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                    
                    a[i + j] = ((a[i + j] + 0ll) * x) % mod, a[i + j + k] =  (a[i + j + k] + 0ll) * x % mod;
                    
                    if(a[i + j] < 0) a[i + j] += mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                }
    }

    void assign(int v1[]) {
        for(int i = 0; i < n; i++) {
            a[i] = v1[i];
        }
        XOR(a, 1);
    }

    void solve(int v2[]) {
        for(int i = 0; i < n; i++) {
            b[i] = v2[i];
        }
        XOR(b, 1);
        mul();
    }

    void end() {
        XOR(a, quick(2ll, mod - 2));
    }
}

const int N = 1e5 + 10, M = 3e5 + 10;
const int T = 145000;
int h[N], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];

int f[N], a[49][T];
set<int> s[N];

int n, m;
void add(int a, int b, int c)  // 添加一条边a->b，边权为c
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) {
                is_bridge[i] = is_bridge[i ^ 1] = true;
            }    
        }
        else if (i != (from ^ 1)) { //非反向边
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    memset(f, 0, sizeof f);
    memset(a, 0, sizeof a);
    
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }

    tarjan(1, -1);
    
    int xo = 0;
    for (int i = 0; i < idx; i += 2 ) {
        int u = e[i], v = e[i ^ 1], c = w[i];
        s[id[u]].insert(u);
        s[id[v]].insert(v);
        if (is_bridge[i]) {
           xo ^= c;
        } else {
            f[id[u]] ^= c;
        }
    }
    
    int match[N];
    int j = 0;
    for(int i = 1; i <= dcc_cnt; i++) {
        if(s[i].size() == 1) continue;
        match[i] = j;
        j++;
    }
    
    for (int i = 0; i < idx; i += 2 ) {
        int u = e[i], v = e[i ^ 1], c = w[i];
        if (is_bridge[i]) {
           
        } else {
            int which = id[u];
            a[match[which]][f[which] ^ c] ++; //delete one edge
        }
    }
    
    vector<int> all;
    for(int i = 1; i <= dcc_cnt; i++) {
        if(s[i].size() == 1) continue;
        //a[match[i]][f[i]]++; //non delete
        all.push_back(match[i]);
    }
    if(all.size() == 0) {
        cout << "1 1" << endl;
        return;
    }
    
    FWT :: n = T;
    FWT :: assign(a[all[0]]);
    FWTCHECK :: n = T;
    FWTCHECK :: assign(a[all[0]]);
    for(int i = 1; i < all.size(); i++) {
        FWT :: solve(a[all[i]]);
        FWTCHECK :: solve(a[all[i]]);
    }
    FWT :: end();
    FWTCHECK :: end();
    
    int res = 1e9, ways = 0;
    for(int i = 0; i < T; i++) {
        if((FWT :: a[i] > 0 || FWTCHECK :: a[i] > 0) && (i ^ xo) < res) {
            res = i ^ xo;
            ways = FWT :: a[i];
        }
    }

    cout << res << " " << ways << endl;
}

int main()
{
    solve();
    return 0;
}
