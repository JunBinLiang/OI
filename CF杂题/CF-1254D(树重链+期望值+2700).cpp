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


const int N = 1e5 + 5e4 + 10, mod = 998244353;
vector<int> g[N];
int sz[N], dep[N], fa[N], son[N], top[N];
int ids[N];
ll add[N];
int n, m, cnt = 0;

struct Node {
  int l, r;
  ll add, sum;
} tr[N * 4];

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    tr[id].sum = 0;
    return;
  }
  int mid = l + (r - l) / 2;
  tr[id * 2 + 1] = {l, mid, 0, 0};
  tr[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, ll add) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e) {
    tr[id].add += add;
    tr[id].add %= mod;
    tr[id].sum += add;
    tr[id].sum %= mod;

    if(tr[id].add < 0) tr[id].add += mod;
    if(tr[id].sum < 0) tr[id].sum += mod;

    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tr[id].add != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].add);
    update(right, tr[right].l, tr[right].r, tr[id].add);
    tr[id].add = 0;
  }

  if(e <= mid) {
    update(left, s, e, add);
  } else if(s >= mid + 1) {
    update(right, s, e, add);
  } else {
    update(left, s, mid, add);
    update(right, mid + 1, e, add);
  }
}

ll query(int id, int s, int e) {
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tr[id].add != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].add);
    update(right, tr[right].l, tr[right].r, tr[id].add);
    tr[id].add = 0;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}


void dfs(int pa, int root, int h) {
    fa[root] = pa;
    sz[root] = 1;
    dep[root] = h;
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
    if(son[root] == -1) return;
    dfs1(root, son[root], line);
    for(int& nxt : g[root]) {
        if(nxt == pa || nxt == son[root]) continue;
        dfs1(root, nxt, nxt); //a new heavy line
    }
}

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}
//1st: 5 2 4 2 2
//add
//2nd: 6 10 6 8 8 


//爬链
void solve() {
    memset(son, -1, sizeof son);
    memset(add, 0, sizeof add);

    scanf("%d%d", &n, &m);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v); 
        g[v].push_back(u);
    }

    dfs(-1, 0, 0);
    dfs1(-1, 0, 0);
    tr[0] = {0, n - 1, 0, 0};
    build(0);
    ll inv = modInverse(n, mod);

    for(int i = 0; i < m; i++) {
        int op, u, d;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &u, &d);
            u--;
            
            ll x = (n + 0ll) * d;
            x %= mod;
            update(0, ids[u], ids[u], x);
            
            int l = ids[u], r = l + sz[u] - 1;
            
            if(l - 1 >= 0) {
                ll t = (sz[u] + 0ll) * d;;
                t %= mod;
                update(0, 0, l - 1, t);
            }
            if(r + 1 <= n - 1) {
                ll t = (sz[u] + 0ll) * d;;
                t %= mod;
                update(0, r + 1, n - 1, t);
            }

            if(son[u] != -1) {
                int nxt = son[u];
                ll t = (n - sz[nxt] + 0ll) * d;
                t %= mod;
                update(0, ids[nxt], ids[nxt] + sz[nxt] - 1, t);
            }
            

            add[u] += d;
            add[u] %= mod;

        } else {
            scanf("%d", &u);  
            u--;  
            ll res = query(0, ids[u], ids[u]);
            
            while(u != 0 && u != -1) {
                if(add[fa[top[u]]] != 0) {
                    int v = top[u];
                    ll x = add[fa[top[u]]];
                    ll size = n - sz[v];
                    x *= size;
                    x %= mod;
                    res += x;
                    res %= mod;
                }
                u = fa[top[u]];
            }
            res *= inv;
            res %= mod;
            printf("%lld\n", res);        
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
