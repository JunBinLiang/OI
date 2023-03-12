#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;


int n;
const int N = 1e5 + 10, M = N;
int h[N], e[M], ne[M], idx;
int dp[N], res[N];
int cnt = 0;

vector<int> g[N];

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void go(int pa, int root) {
    for(int& to : g[root]){
        if(to != pa) {
            add(root, to);
            go(root, to);
        }
    }
}

void dfs(int pa, int root, int k) {
    int mx1 = 0, mx2 = 0;
    dp[root] = 0;
    for(int i = h[root]; ~i; i = ne[i]){
        dfs(root, e[i], k);
        if(dp[e[i]] >= mx1) {
            mx2 = mx1;
            mx1 = dp[e[i]];
        } else if(dp[e[i]] > mx2) {
            mx2 = dp[e[i]];
        }
    }

    if(mx1 + mx2 + 1 >= k) {
        cnt++;
    } else {
        dp[root] = mx1 + 1; 
    }
}

void divide(int l, int r, int s, int e) {
    if(l > r || s > e) return;
    if(s == e) {
        for(int i = l; i <= r; i++) {
            res[i] = s;
        }
        return;
    }

    int midK = l + (r - l) / 2;
    cnt = 0;
    dfs(-1, 1, midK);
    res[midK] = cnt;
    divide(l, midK - 1, cnt, e);
    divide(midK + 1, r, s, cnt);
} 

void solve() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        //add(u, v);
        //add(v, u);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    go(-1, 1);

    divide(1, n, 0, n);
    for(int i = 1; i <= n; i++) {
        printf("%d\n", res[i]);
    }
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
