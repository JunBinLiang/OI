#include <iostream>
#include <vector>
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

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

int n, m;
const int N = 1e5 + 10;
vector<int> g[N];
ll res = 0;
ll in[N], out[N];

void rev(int u) {
    for(int nxt : g[u]) {
        res -= in[u];
        res -= out[nxt];
    }
    
    for(int nxt : g[u]) {
        out[u]--;
        in[nxt]--;
        in[u]++;
        out[nxt]++;
        g[nxt].push_back(u);
    }
    
    for(int nxt : g[u]) {
        res += in[nxt];
    }
    g[u].clear();
}

void solve() {
    scanf("%d%d", &n, &m);
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(u > v) swap(u, v);
        // u < v
        g[u].push_back(v);
        in[v]++;
        out[u]++;
    }
    for(int i = 1; i <= n; i++) {
        res += (in[i] * out[i]);
    }

    int q;
    scanf("%d", &q);
    printf("%lld \n", res);
    for(int i = 0; i < q; i++) {
        int u;
        scanf("%d", &u);
        rev(u);
        printf("%lld \n", res);
    }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
