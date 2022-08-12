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

const int N = 50010, M = 200010, S = 1000010;
int n, m, len;
int cnt[S];
int a[N], ans[M];
struct Query
{
    int id, l, r;
}q[M];

void add(int x, int& res)
{
    if (!cnt[x]) res ++ ;
    cnt[x] ++ ;
}

void del(int x, int& res)
{
    cnt[x] -- ;
    if (!cnt[x]) res -- ;
}

int get(int x)
{
    return x / len;
}

bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

//complexity 
//if block : sqrt(n)
//r : n sqrt(n)
//l : m sqrt(n)

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    scanf("%d", &m);
    len = max(1, (int)sqrt((double)n * n / m));

    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    
    sort(q, q + m, cmp);
    
    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++ )
    {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(a[ ++ i], res);
        while (i > r) del(a[i -- ], res);
        while (j < l) del(a[j ++ ], res);
        while (j > l) add(a[ -- j], res);
        ans[id] = res;
    }
    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}
