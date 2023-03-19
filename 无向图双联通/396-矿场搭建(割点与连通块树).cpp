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
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N = 1010, M = 1010;
int n, m, root;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int dcc_cnt;
vector<int> dcc[N];
bool cut[N];

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;
    
    if (u == root && h[u] == -1)
    {
        dcc_cnt ++ ;
        dcc[dcc_cnt].push_back(u);
        return;
    }
    
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j])
            {
                cnt ++ ;
                if (u != root || cnt > 1) cut[u] = true;
                ++ dcc_cnt;
                int y;
                do {
                    y = stk[top -- ];
                    dcc[dcc_cnt].push_back(y);
                } while (y != j);
                dcc[dcc_cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}



bool solve(int t) {
    scanf("%d", &m);
    if(m == 0) {
        return false;
    }
    
    idx = n = timestamp = top = dcc_cnt = 0;
    
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    memset(cut, 0, sizeof cut);
        
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        n = max(n, a), n = max(n, b);
        add(a, b), add(b, a);
    }
    
    ull num = 1;
    int res = 0;
    
    for(root = 1; root <= n; root ++ )
        if (!dfn[root]) {
            tarjan(root);
        }
    
    
    for(int i = 1; i <= dcc_cnt; i++) {
        int cnt = 0;
        for(int& v : dcc[i]) {
            if(cut[v]) cnt++;
        }
        
        if(cnt == 0) {
            if(dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
            else res++; //孤立点，从自己出来
        } else if(cnt == 1) {
            res ++, num *= dcc[i].size() - 1;
        }
        
        dcc[i].clear(); //clear
    }
    
    printf("Case %d: %d %llu\n", t, res, num);
    return true;
}

int main() {
    int t = 1;
    while(solve(t)) {
        t++;
    }
    return 0;
}
