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


int n, m;
const int N = 2010;
int p[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

struct Edge
{
    int a, b, w;
    bool operator< (const Edge &t) const
    {
        return w < t.w;
    }
};

vector<Edge> e;

void solve() {
    cin >> n >> m;
    
    for(int i = 0; i < N; i++) p[i] = i;
    
    int res = 0;
    for(int i = 0; i < m; i++) {
        int t, u, v, w;
        cin >> t >> u >> v >> w;
        if(t == 1) {
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) p[r1] = r2;
            res += w;
        } else {
            e.push_back({u, v, w});
        }
    }
    
    sort(e.begin(), e.end());
    for(int i = 0; i < e.size(); i++) {
        int u = e[i].a, v = e[i].b, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        if(r1 != r2) {
            p[r1] = r2;
            res += w;
        }
    }
    
    cout << res << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}



