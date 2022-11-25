#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define pb push_back

const int N = 1010;
int f[N][20], cost[N][N];
int a[N], v[N];
int dist[N], l[N], r[N];
int n, m;

struct Segment
{
    int root;
    int tot_sum, tot_size;
    int tree_sum, tree_size;

    int cost()
    {
        int mid = v[root];
        return mid * tree_size - tree_sum + (tot_sum - tree_sum) - ((tot_size - tree_size) * mid);
    }
}stk[N];

int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (v[x] < v[y]) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[l[x]] < dist[r[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}

int pop(int x)
{
    return merge(l[x], r[x]);
}


void getCost(int u) {
    int tt = 0, res = 0;
    for(int i = u; i <= n; i++) {
        auto cur = Segment({i, v[i], 1, v[i], 1});
        l[i] = r[i] = 0; dist[i] = 1;
        while(tt != 0 && v[cur.root] < v[stk[tt].root]) {
            res -= stk[tt].cost();
            cur.root = merge(cur.root, stk[tt].root);
            bool is_pop = cur.tot_size % 2 && stk[tt].tot_size % 2;
            cur.tot_size += stk[tt].tot_size;
            cur.tot_sum += stk[tt].tot_sum;
            cur.tree_size += stk[tt].tree_size;
            cur.tree_sum += stk[tt].tree_sum;
            if (is_pop) {
                cur.tree_size --;
                cur.tree_sum -= v[cur.root];
                cur.root = pop(cur.root);
            }
            tt--;
        }
        stk[ ++ tt] = cur;
        res += cur.cost();
        cost[u][i] = min(cost[u][i], res);
    }   
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(cost, 0x3f, sizeof cost);
    //递增
    for (int i = 1; i <= n; i ++ ) v[i] = a[i] - i;
    for (int i = 1; i <= n; i ++ ) getCost(i);
    //递减
    for (int i = 1; i <= n; i ++ ) v[i] = -a[i] - i;
    for (int i = 1; i <= n; i ++ ) getCost(i);
    
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int le = 1; le <= i; le++) {
                f[i][j] = min(f[i][j], f[i - le][j - 1] + cost[i - le + 1][i]);
            }
        }
    }
    printf("%d\n", f[n][m]);
    return 0;
}
