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
#include<fstream>
 
 
using namespace std;  
using ll = long long;
#define pb push_back

 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 3e5 + 10;
const int mod = 998244353;
int n, k;
vector<int> g[N], c[N];
pair<int, int> edges[N];
int color[N], d[N], lc[N];
int f[N][20];
int dp[N][2];

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 19; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 19; i >= 0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void dfs1(int pa, int root, int h) {
    d[root] = h;
    f[root][0] = pa;
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        dfs1(root, nxt, h + 1);
    }
}

void dfs(int pa, int root) { //0: no color   1 : has color

    vector<int> childs;
    int last = -1;
    for(int& nxt : g[root]) {
        if(nxt == pa || nxt == last) continue;
        last = nxt;
        dfs(root, nxt);
        childs.pb(nxt);
    }
    
    

    if(color[root] == 0) {
        dp[root][0] = 1;
        for(int& nxt : childs) {
            dp[root][0] = ((dp[nxt][1] + dp[nxt][0] + 0ll) * (dp[root][0])) % mod;
        }
        
        vector<int> l(childs.size());
        vector<int> r(childs.size());
        
        for(int i = 0; i < childs.size(); i++) {
            int nxt = childs[i];
            l[i] = (int)(dp[nxt][0] + dp[nxt][1]);
            if(i) l[i] = ((l[i - 1] + 0ll) * (l[i])) % mod;
            l[i] %= mod;
        }
        
        for(int i = childs.size() - 1; i >= 0; i--) {
            int nxt = childs[i];
            r[i] = (int)(dp[nxt][0] + dp[nxt][1]);
            if(i + 1 < childs.size()) r[i] = ((r[i] + 0ll) * (r[i + 1])) % mod;
            r[i] %= mod;
        }
        
        for(int i = 0; i < childs.size(); i++) {
            int nxt = childs[i];
            if(dp[nxt][1] > 0) {
                ll v = dp[nxt][1];
                if(i - 1 >= 0) v *= l[i - 1];
                v %= mod;
                if(i + 1 < childs.size()) v *= r[i + 1];
                v %= mod;
                dp[root][1] += (int)(v);
                dp[root][1] %= mod;
            }
        }
        
        
    } else {
        dp[root][0] = 0;
        dp[root][1] = 1;
        for(int& nxt : childs) {
            dp[root][1] = ((dp[nxt][1] + dp[nxt][0] + 0ll) * dp[root][1]) % mod;
        }
        
    }
    
    //cout <<"dfs:  " << pa << "  " << root << "  " << endl;
    //cout << dp[root][0] << "  " << dp[root][1] << endl << endl;

}

void solve() {
    memset(color, 0, sizeof color);
    memset(dp, 0, sizeof dp);
    memset(f, -1, sizeof f);

    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        c[x].pb(i);
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].pb(v);
        g[v].pb(u);
        edges[i] = {u, v};
    }

    for(int i = 1; i <= n; i++) {
        lc[i] = i;
    }

    dfs1(-1, 1, 0);

    for(int i = 1; i < 20; i++) {
        for(int j = 1; j <= n; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
        }
    }
    
    //color the tree
    for(int i = 1; i <= k; i++) {
        vector<int>& nodes = c[i];
        int lca = nodes[0];
        
        for(int j = 1; j < nodes.size(); j++) {
            lca = LCA(lca, nodes[j]);
        }
        
        for(int& u : nodes) {
            int cur = u;
            while(cur != -1) {
                if(color[cur] != 0 && color[cur] != i) {
                    cout << 0 << endl;
                    return;
                }
                if(color[cur] == i) {
                    break;
                }
                lc[cur] = lca;
                color[cur] = i;
                if(cur == lca) break;
                cur = f[cur][0];
            }
        }
    }
    
    /*for(int i = 1; i <= n; i++) cout << i << "  " << lc[i] << endl;
    cout << endl;
    
    for(int i = 1; i <= n; i++) cout << color[i] << " ";
    cout << endl;
    
    cout << endl;*/
    

    for(int i = 0; i <= n; i++) {
        g[i].clear();
    }

    for(int i = 0; i < n - 1; i++) {
        auto [u, v] = edges[i];
        int r1 = lc[u], r2 = lc[v];
        if(r1 == r2) continue;
        g[r1].pb(r2);
        g[r2].pb(r1);
    }
    
    for(int i = 0; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
    }
    
    dfs(-1, lc[1]);
    cout << dp[lc[1]][1] << endl;
} 

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
