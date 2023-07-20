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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 

const int N = 5e5 + 10, M  = N * 2;


int n, m;
int h[N], e[M], ne[M], idx;
bool st[N], ans[N];
int qq[N], d[N];

pair<int, int> a[N];
vector<pair<int, int>> b;
vector<pair<int, int>> c;


void print(vector<pair<int, int>>& v) {
    for(auto pa : v) {
        cout << pa.first << " " << pa.second << endl;
    }
}

void add(int a, int b)
{
  e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa) {
            res += get_size(e[i], u);
        }
            
    return res;
}

int get_wc(int fa, int u, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(u, j, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}

void dfs(int fa, int u, int dep) {
    if(ans[u]) {
        b.push_back({u, dep});
    }
    if(qq[u] != -1) {
        c.push_back({u, dep});
    }
    if(st[u]) {
        return;
    }
    for(int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == fa) continue;
        dfs(u, j, dep + 1);
    }
}

void cal(int u)
{
    if (st[u]) return;
    get_wc(-1, u, get_size(u, -1), u);
    st[u] = true;  // 删除重心
    vector<int> child;
    for (int i = h[u]; ~i; i = ne[i])
    {
        child.push_back(e[i]);
    }

    unordered_map<int, vector<int>> f;
    if(ans[u]) {
        f[0].push_back(u);
    }

    for(int& nxt : child) {
        b.clear();
        c.clear();
        dfs(u, nxt, 1);

        for(int i = 0; i < c.size(); i++) {
            int node = c[i].first, dis = c[i].second;
            int w = qq[node] - dis;
            vector<int> key;
            for(auto it = f.begin(); it != f.end(); it++) {
                if(it -> first == w) continue;
                key.push_back(it -> first);
                for(int& node : (it -> second))  {
                    ans[node] = false;
                }
            }
            for(int k : key) f.erase(k);
        }

        for(auto& pa : b) {
            int node = pa.first, dis = pa.second;
            if(qq[u] != -1) {
                if(dis != qq[u]) {
                    ans[node] = false;
                } else {
                    f[dis].push_back(node);  
                }
            } else {
                f[dis].push_back(node);
            }
        }
    }

    
    //do reverse 1 more time
    reverse(child.begin(), child.end());
    f.clear();
    if(ans[u]) {
        f[0].push_back(u);
    }

    for(int& nxt : child) {
        b.clear();
        c.clear();
        dfs(u, nxt, 1);

        for(int i = 0; i < c.size(); i++) {
            int node = c[i].first, dis = c[i].second;
            int w = qq[node] - dis;
            vector<int> key;
            for(auto it = f.begin(); it != f.end(); it++) {
                if(it -> first == w) continue;
                key.push_back(it -> first);
                for(int& node : (it -> second))  {
                    ans[node] = false;
                }
            }
            
            for(int k : key) f.erase(k);
        }

        for(auto& pa : b) {
            int node = pa.first, dis = pa.second;
            if(qq[u] != -1) {
                if(dis != qq[u]) {
                    ans[node] = false;
                } else {
                    f[dis].push_back(node);
                }
            } else {
                f[dis].push_back(node);
            }
        }
    }


    for (int i = h[u]; ~i; i = ne[i]) cal(e[i]);
} 




void solve() {
    memset(h, -1, sizeof h);
    memset(st, 0, sizeof st);
    memset(ans, 0, sizeof ans);
    memset(qq, -1, sizeof qq);
    idx = 0;

    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        if(i) {
            qq[a[i].first] = a[i].second;
        }
    }

    memset(d, -1, sizeof d);
    d[a[0].first] = 0;
    queue<int> q;
    q.push(a[0].first);
    while(q.size()) {
        int u = q.front(); q.pop();
        if(d[u] == a[0].second) { //answer point
            ans[u] = true;
        }
        for(int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if(d[j] == -1) {
                d[j] = d[u] + 1;
                q.push(j);
            }
        }
    }
    if(m > 1) {
        cal(1);
    }

    //cout << "ans _________________" << endl;
    vector<int> res;
    for(int i = 1; i <= n; i++) {
        if(ans[i]) {
            if(qq[i] != -1) {
                if(qq[i] == 0) res.push_back(i);
            } else {
                res.push_back(i);
            }
        }
    }
    cout << res.size() << endl;
    for(int x : res) printf("%d\n", x); 
} 
    

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
