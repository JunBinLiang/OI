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

const int N = 2e5 + 1000;
const int M = 19;
vector<int> g[N];
int f[N][M];
int d[N], sz[N], son[N], top[N], ids[N];
int cnt = 0;
int n, m;

struct Fenwick {
    int tree[N];
    int SIZE = N;
    void init() {
        memset(tree, 0, sizeof tree);
    }

    void update(int i, int val) {
        i++;
        while(i < SIZE){
            tree[i] += val;
            i += (i & -i);
        }
    }
    int pre(int i) {
        int sum = 0;
        while(i>0){
            sum += tree[i];
            i -= ( i & -i);
        }
        return sum;
    }
    int query(int i, int j) {
        return pre(j + 1) - pre(i);
    }
} tr[21];

void dfs(int pa, int root, int h){
    f[root][0] = pa;
    d[root] = h;
    sz[root] = 1;
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        dfs(root, nxt, h + 1);
        sz[root] += sz[nxt];
        if(son[root] == -1) {
            son[root] = nxt;
        } else {
            if(sz[nxt] > sz[son[root]]) {
                son[root] = nxt;
            }
        }
    }
}

void dfs1(int pa, int root, int line) {
    top[root] = line;
    ids[root] = cnt;
    cnt++;
    //cout << "dfs  " << pa + 1 << " " << root + 1 << endl;
    if(son[root] == -1) return;
    dfs1(root, son[root], line);
    for(int& nxt : g[root]) {
        if(nxt == pa || nxt == son[root]) continue;
        dfs1(root, nxt, nxt); //a new heavy line
    }
}

void update_path(int u, int v, int k, int dth) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]]) swap(u, v);
        //update(0, ids[top[u]], ids[u], k);
        int l = ids[top[u]], r = ids[u];
        tr[dth].update(l, k);
        tr[dth].update(r + 1, -k);
        u = f[top[u]][0];
    }
    if(d[u] < d[v]) swap(u, v);
    //update(0, ids[v], ids[u], k);
    int l = ids[v], r = ids[u];
    tr[dth].update(l, k);
    tr[dth].update(r + 1, -k);
}

void update_point(int u, int k, int dth) {
    tr[dth].update(ids[u], k);
    tr[dth].update(ids[u] + 1, -k);
}

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }
  
  for(int i = M - 1; i >= 0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = M - 1; i >= 0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    //拉长整棵树
    int root = 0;
    int nxt = n;
    for(int i = 0; i <= 25; i++) {
        g[nxt].push_back(root);
        g[root].push_back(nxt);
        root = nxt;
        nxt++;
    }


    memset(f, -1, sizeof f);
    memset(son, -1, sizeof son);
    dfs(-1, root, 0);
    dfs1(-1, root, root);
    
    for(int i = 1; i < M; i++) {
        for(int j = 0; j < N; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
        }
    }
    for(int i = 0; i < 21; i++) tr[i].init();
    
    
    //cout << "root  " << root << endl;
    /*for(int i = 0; i <= root; i++) {
        cout << i + 1 << "  " << ids[i] << endl;
    }*/
    


    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int u;
            scanf("%d", &u);
            u--;
            ll res = 0;
            for(int j = 0; j <= 20; j++) {
                res += tr[j].query(0, ids[u]);
                //cout <<"query : " <<  j << "  " << u + 1 << "  " << tr[j].query(0, ids[u]) << endl;
                u = f[u][0];
            }
            printf("%d\n", res);
        } else {
            int u, v, k, d;
            scanf("%d%d%d%d", &u, &v, &k, &d);
            u--; v--;
            int lca = LCA(u, v);
            update_path(u, v, k, d);
            
            //cout << "update1  " << u + 1 << " "  << v + 1 << " " << lca + 1 << endl;
            
            if(d - 1 >= 0) {
                update_point(lca, k, d - 1);
            }
            
            int cur = f[lca][0];
            for(int j = 1; j <= d; j++) {
                update_point(cur, k, d - j);
                if(d - j - 1 >= 0) {
                    update_point(cur, k, d - j - 1);
                }
                cur = f[cur][0];
            }
        }
    }
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
