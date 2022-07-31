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


const int N = 110, M = 10010;
int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt;
int in[N], out[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}


int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i++) {
        int m;
        int to;
        while(true) {
            cin >> to;
            if(!to) break;
            add(i, to);
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) tarjan(i);
    }
    

    for(int i = 1; i <= n; i++) {
        for(int j = h[i]; j != -1; j = ne[j]) {
            int id1 = id[i], id2 = id[e[j]];
            if(id1 != id2) {
                in[id2]++;
                out[id1]++;
            }
        }
    }
    
    int ans1 = 0, ans2 = 0;
    for(int i = 1; i <= scc_cnt; i++) {
        if(!in[i]) {
            ans1++;
        }
        if(!out[i]) {
            ans2++;
        }
    }
    
    
    cout << ans1 << endl;
    
    if(scc_cnt == 1) cout << 0 << endl;
    else cout << max(ans1, ans2) << endl;
    
    return 0;
}
