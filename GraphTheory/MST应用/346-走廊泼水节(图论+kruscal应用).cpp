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
typedef pair<double, double> PDD;

const int N = 7000;

struct Edge
{
    int u, v, w;
    bool operator< (const Edge &t)const
    {
        return w < t.w;
    }
} e[N];
int p[N], sz[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}



int n, m;
void solve() {
    cin >> n;
    m = n - 1;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    
    for(int i = 0; i <= n; i++) p[i] = i, sz[i] = 1;
    
    sort(e, e + m);
    ll res = 0;
    for(int i = 0; i < m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        res += ((w + 1) * (sz[r1] * sz[r2] - 1));
        p[r1] = r2;
        sz[r2] += sz[r1];
        
        
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
