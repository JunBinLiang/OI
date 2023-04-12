
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector

struct Node {
    int fax, fay, w;
    bool o;
};

const int N = 2e5 + 10;
int L[N], R[N], rk[N], p[N];
int n, m;

int find(int u) {
    if(p[u] == u) return u;
    return find(p[u]);
}

vector<pair<int, int>> connect[N * 4];
vector<Node> stk[N * 4];
vector<int> nodes[N];
bool ok[N];

void add(int id, int l, int r, int u, int v, int s, int e) {
    if(l == s && r == e) {
        connect[id].push_back({u, v});
        //cout << l << " " << r << "  | "<< u << " " << v << endl;
        return;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(e <= mid) {
        add(left, l, mid, u, v, s, e);
    } else if(s >= mid + 1) {
        add(right, mid + 1, r, u, v, s, e);
    } else {
        add(left, l, mid, u, v, s, mid);
        add(right, mid + 1, r, u, v, mid + 1, e);
    }
}

void dfs(int id, int l, int r) {

    for(pair<int, int>& e : connect[id]) {
        int u = e.first, v = e.second;
        int fax = find(u), fay = find(v);
        if(rk[fax] > rk[fay]) {
            swap(fax, fay);
        }
        if(fax != fay) {
            p[fax] = fay;
            stk[id].push_back({fax, fay, rk[fax] == rk[fay], ok[fay]});
            if(rk[fay] == rk[fax]) rk[fay]++;
            ok[fay] = find(1) == fay;
        }
    }
    
    if(l != r) {
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        dfs(left, l, mid);
        dfs(right, mid + 1, r);
    } else {
        /*for(int i = 1; i <= n; i++) {
            if(find(i) == find(1)) res.insert(i);
        }*/
    }

    while(stk[id].size() > 0) {
        auto pa = stk[id].back(); stk[id].pop_back();
        int fax = pa.fax, fay = pa.fay, w = pa.w;
        bool o = pa.o;
        if(ok[fay]) {
            ok[fax] = ok[fay] = true;
        } else {
            ok[fay] = o;
        }
        p[fax] = fax;
        rk[fay] -= w;
    }
    //cout << endl;
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &L[i], &R[i]);
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(L[u] > L[v]) {
            swap(u, v);
        }
        if(R[u] < L[v]) continue;
        int l = max(L[u], L[v]), r = min(R[u], R[v]);
        add(0, 0, N - 1, u, v, l, r);
    }
    
    memset(rk, 0, sizeof rk);
    memset(ok, 0, sizeof ok);
    for(int i = 0; i <= n; i++) p[i] = i, nodes[i].push_back(i);
    ok[1] = true;
    dfs(0, 0, N - 1);

    for(int i = 1; i <= n; i++) {
        if(ok[i]) cout << i << " ";
    }
    cout << endl;

}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

/*
6 5
1 1
1 2
1 2
1 2
2 2
2 2

1 2
2 3
3 4
4 5
5 6

*/
