#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define pb push_back

const int N = 1e6 + 10;
int a[N], dist[N], l[N], r[N];
ll ans[N];
int n;


//最大堆
int merge(int x, int y)
{
    if(!x) return y;
    if(!y) return x;
    if (a[x] < a[y]) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}

int pop(int x)
{
    return merge(l[x], r[x]);
}

struct Segment
{
    int end, root, size;
}stk[N];

int main() {
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        a[i] -= i;
    }
    
    int tt = 0;
    for(int i = 1; i <= n; i++) {
        auto cur = Segment({i, i, 1});
        dist[i] = 1;
        while(tt != 0 && a[cur.root] < a[stk[tt].root]) {
            cur.root = merge(cur.root, stk[tt].root);
            if (cur.size % 2 && stk[tt].size % 2)
                cur.root = pop(cur.root);
            cur.size += stk[tt].size;
            tt--;
        }
        stk[ ++ tt] = cur;
    }
    
    for (int i = 1, j = 1; i <= tt; i ++ )
    {
        while (j <= stk[i].end)
            ans[j ++ ] = a[stk[i].root];
    }
    
    ll res = 0;
    for (int i = 1; i <= n; i ++ ) res += abs(a[i] - ans[i]);
    printf("%lld\n", res);
    for (int i = 1; i <= n; i ++ ) {
        printf("%lld ", ans[i] + i);
    }
    return 0;
}
