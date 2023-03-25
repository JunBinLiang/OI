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

const int N = 8e5 + 10;
int tr[N][26], d[N], idx = 0;
vector<int> g[N], f[N];
char s[N];
int sum = 0; vector<pair<int, int>> res;
set<int> s1, s2;
int n;
//6:10 - 6 : 45

void add(int id) {
    int len = strlen(s);
    int u = 0, cnt = 0;
    
    for(int i = 0; i < len; i++ ) {
        int c = s[i] - 'a';
        if(!tr[u][c]) tr[u][c] = ++idx;
        cnt++;
        u = tr[u][c];
        d[u] = cnt;
    }
    g[u].push_back(id);
}

void find(int id) {
    int len = strlen(s);
    int u = 0;
    for(int i = 0; i < len; i++) {
        int c = s[i] - 'a';
        if(!tr[u][c]) {
            f[u].push_back(id);
            return;
        }
        u = tr[u][c];
    }
    f[u].push_back(id);
}


void dfs(int u) {

    for(int i = 0; i < 26; i++) {
        if(!tr[u][i]) continue;
        int nxt = tr[u][i];
        dfs(nxt);
        if(g[nxt].size() > g[u].size()) swap(g[nxt], g[u]);
        for(int x : g[nxt]) g[u].push_back(x);
        
        if(f[nxt].size() > f[u].size()) swap(f[nxt], f[u]);
        for(int x : f[nxt]) f[u].push_back(x);
    }

    while(g[u].size() > 0 && f[u].size() > 0) {
        int t1 = g[u].back(); g[u].pop_back();
        int t2 = f[u].back(); f[u].pop_back();
        s1.erase(t1); s2.erase(t2);
        res.push_back({t1, t2});
        sum += d[u];
    }
}

void solve() {
    scanf("%d", &n);
    memset(tr, 0, sizeof tr);
    d[0] = 0;

    for(int i = 1; i <= n; i++) {
        scanf("%s", s);
        add(i);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%s", s);
        find(i);
    } 

    for(int i = 1; i <= n; i++) s1.insert(i), s2.insert(i);

    dfs(0);

    while(s1.size() > 0 && s2.size() > 0) {
        auto it1 = s1.begin();
        auto it2 = s2.begin();
        int u = *it1, v = *it2;
        res.push_back({u, v});
        s1.erase(u); s2.erase(v);
    }

    printf("%d\n", sum);
    for(auto& p : res) {
        printf("%d %d\n", p.first, p.second);
    }
}

int main() {
    solve();
    return 0;
}
