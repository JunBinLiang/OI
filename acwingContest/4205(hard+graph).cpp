#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector






//3 : 50 - 3：54

int n;
const int N = 1e5 + 10;
vector<int> g[N];
int cnt[2], col[N];
int in[N];
void dfs(int pa, int root, int c) {
    cnt[c]++;
    col[root] = c;
    for(int & nxt : g[root]) {
        if(nxt == pa) continue;
        dfs(root, nxt, c ^ 1);
    }
}

void solve() {
    scanf("%d", &n);
    memset(in, 0, sizeof in);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v); g[v].push_back(u);
        in[u]++;
        in[v]++;
    }

    cnt[0] = cnt[1] = 0;
    dfs(-1, 0, 0);

    ll res = 0;
    for(int i = 0; i < n; i++) {
        int out = in[i], other = cnt[col[i] ^ 1];
        res += (other - out);
    }

    res /= 2;
    cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
