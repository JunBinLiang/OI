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


const int N = 2e5 + 10;
vector<int> g[N];
vector<int> c = {0, 0};

void dfs(int pa, int root, int col) {
    c[col]++;
    for(int nxt : g[root]) {
        if(nxt != pa) {
            dfs(root, nxt, col ^ 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 1, 0);
    cout << min(c[0], c[1]) - 1 << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
