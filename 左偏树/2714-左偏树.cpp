//支持 1. 查询最小 2. 删除最小  3.加数  4. 合并堆

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n;
int idx = 0;
int v[N], dist[N], l[N], r[N];
int nums[N];

bool cmp(int x, int y)
{
    return v[x] < v[y];
}

int find(int x)
{
    if (nums[x] != x) nums[x] = find(nums[x]);
    return nums[x];
}

int merge(int x, int y)
{
    if(!x) return y;
    if(!y) return x;
    if (cmp(y, x)) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}


int main() {
    scanf("%d", &n);
    v[0] = 2e9; nums[0] = 0;
    for(int i = 0; i < n; i++) {
        int op, x, y;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &x);
            v[++ idx] = x;
            dist[idx] = 1;
            nums[idx] = idx;
        } else if(op == 2) {
            scanf("%d%d", &x, &y);
            x = find(x), y = find(y);
            if(x != y) {
                if (cmp(y, x)) swap(x, y);
                nums[y] = x;
                merge(x, y);
            }
        } else if(op == 3) {
            scanf("%d", &x);
            printf("%d\n", v[find(x)]);
        } else {
            scanf("%d", &x);
            x = find(x);
            if (cmp(r[x], l[x])) swap(l[x], r[x]);
            nums[x] = l[x], nums[l[x]] = l[x];
            merge(l[x], r[x]);
        }
    }
    return 0;
}
