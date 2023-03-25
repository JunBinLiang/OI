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
   
using ll = long long;
using namespace std;  

const int N = 2e5 + 10;
int roots[N], idx = 0;
int n, m;

struct Node {
    int l, r;
    int fa, sz;
} tr[N * 40];

int build(int l, int r) {
    int p = ++idx;
    if(l == r) {
        tr[p].sz = 1;
        tr[p].fa = l;
        return p;
    }
    int mid = l + (r - l) / 2;
    tr[p].l = build(l, mid);
    tr[p].r = build(mid + 1, r);
    return p;
}

int update(int pre, int index, int fa, int sz, int l, int r) {
    int p = ++idx;
    tr[p] = tr[pre];
    if(l == r ) {
        tr[p].fa = fa;
        tr[p].sz = sz;
        return p;
    }
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        tr[p].l = update(tr[pre].l, index, fa, sz, l, mid);
    } else {
        tr[p].r = update(tr[pre].r, index, fa, sz, mid + 1, r);
    }
    return p;
}

Node query(int u, int idx, int l, int r) {
    if(l == r) {
        return tr[u];
    }
    int mid = l + (r - l) / 2;
    if(idx <= mid) return query(tr[u].l, idx, l, mid);
    else return query(tr[u].r, idx, mid + 1, r);
}

Node find(int id, int x) {
    Node node = query(id, x, 1, n);
    if(node.fa != x) return find(id, node.fa);
}

void merge(int pre, int cur, int u, int v) {
    Node n1 = find(roots[cur], u), n2 = find(roots[cur], v);
    if(n1.fa != n2.fa) {
        if(n1.sz > n2.sz) swap(n1, n2);
        roots[cur] = update(roots[pre], n1.fa, n2.fa, n1.sz, 1, n);
        roots[cur] = update(roots[cur], n2.fa, n2.fa, n1.sz + n2.sz, 1, n);
    }
}


void solve() {
    scanf("%d%d", &n, &m);
    roots[0] = build(1, n);
    int res = 0;
    for(int i = 1, u, v, k; i <= m; i++) {
        roots[i] = roots[i - 1];
        int op;
        scanf("%d", &op);
        if(op == 1) {  
            scanf("%d%d", &u, &v);
            u ^= res; v ^= res;
            merge(i - 1, i, u, v);
        } else if(op == 2){
            scanf("%d", &k);
            k ^= res;
            roots[i] = roots[k];
        } else {
            scanf("%d%d", &u, &v);
            u ^= res; v ^= res;
            Node n1 = find(roots[i], u);
            Node n2 = find(roots[i], v);
            if(n1.fa == n2.fa) res = 1;
            else res = 0;
            printf("%d\n", res);
        }
    }
}

int main() {
    solve();
    return 0;
}
