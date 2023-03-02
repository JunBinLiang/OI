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





//1:41 - 1:45
int n;
const int N = 1e5 + 10;
vector<int> g[N];
int res = 0;
int dfs(int pa, int root) {
    int cnt = 1;
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        cnt += dfs(root, nxt);
    }
    if(cnt % 2 == 0) {
        res++;
    }
    return cnt;
}

void solve() {
    scanf("%d", &n);
    if(n % 2 == 1) {
        cout << -1 << endl;
        return;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 0);
    cout << res - 1 << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
