#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;



const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
vector<int> g[N];
int sz[N];
ull h[N], h1[N];
bool good[N], good1[N];
int n;

unsigned long long seed=131;
unsigned long long rands(){return (seed=(seed<<15)+(seed<<8)+(seed>>3));}

unsigned long long seed1=6967;
unsigned long long rands1(){return (seed1=(seed1<<15)+(seed1<<8)+(seed1>>3));}

ull dfs(int pa, int u) {
    sz[u] = 1;
    map<ull, int> f;
    ull resH = 1;

    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        ll ha = dfs(u, nxt);
        sz[u] += sz[nxt];
        ha ^= h[sz[nxt]];
        ha %= mod;
        resH += ha;
        resH %= mod;
        if(f.find(ha) == f.end()) f[ha] = nxt;
        else f.erase(ha);
    }

    if(f.size() == 0) {
        good[u] = true;
    } else {
        if(f.size() == 1) {
            auto it = f.begin();
            good[u] = good[it -> second];
        } else {
            good[u] = false;
        }
    }
    return resH;
}

ull dfs1(int pa, int u) {
    sz[u] = 1;
    map<ull, int> f;
    ull resH = 1;
    
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        ll ha = dfs1(u, nxt);
        sz[u] += sz[nxt];
        ha ^= h1[sz[nxt]];
        ha %= mod;
        resH += ha;
        resH %= mod;
        
        if(f.find(ha) == f.end()) f[ha] = nxt;
        else f.erase(ha);
    }

    if(f.size() == 0) {
        good1[u] = true;
    } else {
        if(f.size() == 1) {
            auto it = f.begin();
            good1[u] = good1[it -> second];
        } else {
            good1[u] = false;
        }
    }
    
    return resH;
}

void solve() {
    cin >> n;
    
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 0; i <= n; i++) {
        sz[i] = 0;
        good[i] = good1[i] = false;
        h[i] = rands() % mod;
        h1[i] = rands1() % mod;
    }
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 1);
    dfs1(-1, 1);
    if(good[1] && good1[1]) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
}

int main()
{   
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
