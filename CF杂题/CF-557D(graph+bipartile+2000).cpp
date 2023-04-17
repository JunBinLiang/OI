
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
#define PII pair<long long, int>


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


const int N = 1e5 + 10;
vector<int> g[N];
pair<int, int> e[N];
int col[N], cnt[2];
bool bi = true;
int sz = 0, mx = 0;
void dfs(int u, int c) {
    sz++;
    mx = max(mx, sz);
    col[u] = c;
    cnt[c]++;
    for(int nxt : g[u]) {
        if(col[nxt] == -1) {
            dfs(nxt, c ^ 1);
        } else {
            if(col[nxt] == col[u]) {
                bi = false;
            }
        }
    }
}

void solve() {
    // If a graph is bipartite it doesn't contains any odd length cycles, but, 
    //if a graph is non-bipartite it surely contains at least one odd length cycle.
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        e[i] = {u, v};
    }

    memset(col, -1, sizeof col);
    for(int i = 1; i <= n; i++) {
        if(col[i] == -1) {
            sz = 0;
            dfs(i, 0);
        }
    }

    if(!bi) {
        cout << 0 << " " << 1 << endl;
        return;
    }

    if(m == 0) {//no edge, randomly choose 3 points
        ll x = (n + 0ll) * (n - 1) * (n - 2) / 6;
        cout << 3 << " " << x << endl;
        return;
    }

    

    if(mx <= 2) {
        cout << 2 << " " << ((m + 0ll) * (n - 2)) << endl;
        return;
    }

    ll res = 0;
    memset(col, -1, sizeof col);
    for(int i = 1; i <= n; i++) {
        if(col[i] == -1) {
            cnt[0] = cnt[1] = 0;
            dfs(i, 0);
            ll x = (cnt[0] + 0ll) * (cnt[0] - 1) / 2;
            ll y = (cnt[1] + 0ll) * (cnt[1] - 1) / 2;
            res += x;
            res += y;
        }
    }
    cout << 1 << " " << res << endl;
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

