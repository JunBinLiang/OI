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
#include <iostream>
   
using ll = long long;
using namespace std;  



namespace Fenwick {
  const int SIZE = 2e6 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
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
}

const int N = 1e6 + 10;
int idx = 0, tail = -1;
int ne[N], q[N];
int tr[N][26];
int ids[N], ok[N], in[N], out[N], cnt[N];
char str[N];
vector<int> g[N];

void insert(int id)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
    }
    ids[id] = p;
    ok[id] = 1;
    cnt[p]++;
}

void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    
    tail = tt;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else  
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
                tail = tt;
            }
        }
    }
}

//tree euler tour
void dfs(int pa, int u) {
    
    in[u] = idx;
    if(cnt[u] > 0) {
        Fenwick :: update(idx, cnt[u]);
    }
    idx++;

    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        dfs(u, nxt);
    }

    out[u] = idx;
    if(cnt[u] > 0) {
        Fenwick :: update(idx, -cnt[u]);
    }
    idx++;
}

void solve() {
    int m, n;
    scanf("%d%d", &m, &n);
    
    memset(cnt, 0, sizeof cnt);
    
    for(int i = 1; i <= n; i++) {
        scanf("%s", str);
        insert(i);
    }

    
    Fenwick :: init();
    build();
    
    for(int i = tail; i >= 0; i--) {
        int node = q[i];
        g[ne[node]].push_back(node);
    }
    
    idx = 0;
    dfs(-1, 0);

    for(int i = 0; i < m; i++) {
        scanf("%s", str);
        int len = strlen(str);
        if(str[0] == '-') {
            int k = 0;
            for(int j = 1; j < len; j++) {
                k = k * 10 + str[j] - '0';
            }
            if(!ok[k]) continue;
            ok[k] = 0;
            int nodeId = ids[k];
            Fenwick :: update(in[nodeId], -1);
            Fenwick :: update(out[nodeId], 1);

        } else if(str[0] == '+') {
            int k = 0;
            for(int j = 1; j < len; j++) {
                k = k * 10 + str[j] - '0';
            }
            if(ok[k]) continue;
            ok[k] = 1;
            int nodeId = ids[k];
            Fenwick :: update(in[nodeId], 1);
            Fenwick :: update(out[nodeId], -1);
        } else {
            ll res = 0;
            for(int x = 1, j = 0; x < len; x++) {
                int t = str[x] - 'a';
                while(j && !tr[j][t]) j = ne[j];
                if(tr[j][t]) j = tr[j][t];
                res += Fenwick :: query(0, in[j]);
            }
            printf("%lld\n", res);
        }
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
