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




const int N = 1e5 + 10, INF = 1e9;
char s[N], str[N];
vector<int> all[N], g[N];
int ne[N], nee[N], q[N], ids[N], dep[N], sz[N], idx = 0, tail = -1;
int tr[N][26];
int a[N], res[N];
int n, m;

void insert(int id)
{
    int p = 0, le = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
        dep[p] = ++le;
    }
    ids[p] = id;
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

void dfs(int pa, int u, int id) {
    nee[u] = id;
    if(ids[u] != -1) {
        id = u;
    }
    for(int& nxt : g[u]) {
        if(pa == nxt) continue;
        dfs(u, nxt, id);
    }
}

void solve() {
    memset(ids, -1, sizeof ids);
    memset(nee, 0, sizeof nee);

    scanf("%s", s);
    n = strlen(s);

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
        scanf("%s", str);
        sz[i] = strlen(str);
        insert(i);
    }

    build();
    
    /*for(int i = 0; i < idx; i++) {
        cout << ne[i] << "  ";
    }  cout << endl << endl;*/
    
    for(int i = tail; i >= 0; i--) {
        int node = q[i];
        g[ne[node]].push_back(node);
    }
    dfs(-1, 0, 0);
    
    /*for(int i = 0; i < idx; i++) {
        cout << nee[i] << "  ";
    }  cout << endl << endl;*/

    int j = 0;
    for(int i = 0; i < n; i++) {
        int t = s[i] - 'a';
        while(j && !tr[j][t]) j = ne[j];
        if(tr[j][t]) j = tr[j][t];
        int p = j;
        //sqrt
        while (p)
        {
            if(ids[p] != -1) {
                all[ids[p]].push_back(i);
            }
            p = nee[p];
        }
    }

    for(int i = 0; i < m; i++) {
        auto& v = all[i];
        int k = a[i];
        if(v.size() < k) {
            res[i] = -1;
            continue;
        }
        res[i] = INF;
        for(int j = 0; j < v.size(); j++) {
            if(j + 1 < k) continue;
            int l = j - k + 1, r = j;
            int len = v[r] - (v[l] - sz[i] + 1) + 1;
            res[i] = min(res[i], len);
        }
    }

    for(int i = 0; i < m; i++) {
        printf("%d\n", res[i]);
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
