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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 1e5 + 10;
int n, m;
int a[N], dp[N];

struct Node
{
    int s[2], p, v;
    int sum, rev;
    int last;
    int dest;
}tr[N];
int stk[N];

void pushrev(int x)
{
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x)
{
    tr[x].sum = tr[tr[x].s[0]].sum + tr[tr[x].s[1]].sum + tr[x].v;
    tr[x].dest = max(tr[x].last, max(tr[tr[x].s[0]].dest, tr[tr[x].s[1]].dest));
}

void pushdown(int x)
{
    if (tr[x].rev)
    {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x)
{
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x)
{
    int top = 0, r = x;
    stk[ ++ top] = r;
    while (!isroot(r)) stk[ ++ top] = r = tr[r].p;
    while (top) pushdown(stk[top -- ]);
    while (!isroot(x))
    {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access(int x)  // 建立一条从根到x的路径，同时将x变成splay的根节点
{
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p)
    {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x)  // 将x变成原树的根节点
{
    access(x);
    pushrev(x);
}

int findroot(int x)  // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x); 
    return x;
}

void split(int x, int y)  // 给x和y之间的路径建立一个splay，其根节点是y
{
    makeroot(x);
    access(y);
}

void link(int x, int y)  // 如果x和y不连通，则加入一条x和y之间的边
{
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

void cut(int x, int y)  // 如果x和y之间存在边，则删除该边
{
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0])
    {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    memset(dp, 0, sizeof dp);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tr[i].v = 1;
        tr[i].last = i;
    }
    tr[n + 1].v = 0; //哨兵
    tr[n + 1].last = -1;

    for(int i = n; i >= 1; i--) {
        if(a[i] + i > n) {
            link(i, n + 1);
        } else {
            link(i, i + a[i]);
        }
    }

    for(int i = 0; i < m; i++) {
        int op;
        int idx, v;
        scanf("%d", &op);
        if(op == 0) {
            scanf("%d%d", &idx, &v);
            int old = a[idx];
            if(idx + old <= n) {
                cut(idx, idx + old);
            } else {
                cut(idx, n + 1);
            }

            a[idx] = v;
            if(idx + v <= n) {
                link(idx, idx + v);
            } else {
                link(idx, n + 1);
            }

        } else {
            scanf("%d", &idx);
            split(n + 1, idx);
            printf("%d %d\n", tr[idx].dest, tr[idx].sum);
        }
    }
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
