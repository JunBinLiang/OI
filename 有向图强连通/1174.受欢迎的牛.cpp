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

int n, m;
const int N = 10010, M = 50010;
int h[N], e[M], ne[M], idx;

int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];

int id[N], scc_cnt, Size[N];
int dout[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt] ++ ;
        } while (y != u);
    }
}


int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    
    //缩点
    for (int i = 1; i <= n; i ++ ) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a] ++ ;
        } 
    }
    
    int sum = 0, cnt = 0;
    for(int i = 1; i <= scc_cnt; i ++) {
        if(dout[i] == 0) {
            cnt++;
            sum += Size[i];
        }
    }
    
    if(cnt != 1) sum = 0;
    cout << sum << endl;
    
    return 0; 
}
