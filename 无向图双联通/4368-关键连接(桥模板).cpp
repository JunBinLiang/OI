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

int n;
const int N = 1e5 + 10, M = N * 2;
int e[M], ne[M], h[N], idx;
int dfn[N], low[N], timestamp;
bool is_bridge[M];

vector<pair<int, int>> ans;

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            
            tarjan(j, u);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) {
                ans.push_back({min(u, j), max(u, j)});
            }    
        }
        else if (j != from) { //非反向边
            low[u] = min(low[u], dfn[j]);
        }
    }

    /*if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }*/
}


void solve() {
    
    idx = 0;
    timestamp = 0;
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    ans.clear();
    
    
    //cout << n << endl;
    
    for(int i = 0; i < n; i++) {
        int u;
        scanf("%d", &u);
        string s;
        cin >> s;
        int k = 0;
        for(int j = 1; j < s.size() - 1; j++) {
            k = k * 10 + s[j] - '0';
        }
        
        for(int j = 0; j < k; j++) {
            int v;
            scanf("%d", &v);
            add(u, v);
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(!dfn[i]) tarjan(i, -1);
    }
    
    sort(ans.begin(), ans.end());
    cout << ans.size() << " critical links" << endl;
    for(auto& p : ans) {
        cout << p.first << " - " << p.second << endl;
    }
    cout << endl;
}

int main() {
    while(cin >> n) {
        solve();    
    }
    return 0;
}
