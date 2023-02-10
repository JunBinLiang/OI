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


const int N = 1e6 + 100, M = 1e6 + 100;
int use[N];
int n, m;

struct Edge {
    int u, v;
} e[M];

struct Node
{
    int s[2], p, v;
    int rev;
    int tag = -1;
    int sum = 0;
}tr[N];
int stk[N];

void pushrev(int x)
{
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x)
{
    tr[x].sum = 0;
    if(x > n) { //we only want to color edge
        tr[x].sum = tr[x].v;
    }
    if(tr[x].s[0]) tr[x].sum |= tr[tr[x].s[0]].sum;
    if(tr[x].s[1]) tr[x].sum |= tr[tr[x].s[1]].sum;
}

void pushdown(int x)
{
    if (tr[x].rev)
    {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
    
    if(tr[x].tag != -1) {
        int l = tr[x].s[0], r = tr[x].s[1];
        if(l) tr[l].tag = tr[l].v = tr[l].sum = tr[x].tag;
        if(r) tr[r].tag = tr[r].v = tr[r].sum = tr[x].tag;
        tr[x].tag = -1;
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

void tag(int x, int y, int tag) { //路劲全更新懒标记
    split(x, y);
    splay(y);
    tr[y].v = tr[y].tag = tr[y].sum = tag;
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

bool con(int u, int v) {
    makeroot(u);
    return findroot(v) == u;
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[i] = {u, v};
    }
    
    //路劲修改
    //https://blog.csdn.net/jmsyzldx/article/details/78961946
    //split(x, y), splay(y)
    
    ll res = 0;
    for(int i = 1, j = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
    
        while(con(u, v)) {
            split(u, v);
            splay(v);
            if(tr[v].sum == 0) {
                break;
            }
            
            splay(j + n);
            
            if(tr[j + n].v != 0) {
                int o = tr[j + n].v;
                tag(e[o].u, e[o].v, 0);
                cut(e[j].u, j + n);
                cut(j + n, e[j].v);
                link(e[o].u, o + n);
                link(o + n, e[o].v);
            } else {
                cut(e[j].u, j + n);
                cut(j + n, e[j].v);
            }
            j++;
        }
        
        if(con(u, v)) {
            tag(e[i].u, e[i].v, i);
        } else {
            link(e[i].u, i + n);
            link(i + n, e[i].v);
        }
        res += (i - j + 1);
    }
    cout << res << endl;
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

