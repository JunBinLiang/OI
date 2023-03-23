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

/*
可撤销并查集是支持“撤销连接”操作的并查集，但是这个撤销必须按栈的顺序。
由于需要实现撤销，需要用栈记录所有已经完成过的连接操作。并且不能路径压缩。
https://blog.csdn.net/bunny_1024/article/details/125830704?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125830704-blog-109451857.235%5Ev27%5Epc_relevant_landingrelevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125830704-blog-109451857.235%5Ev27%5Epc_relevant_landingrelevant&utm_relevant_index=2
*/

const int N = 5e5 + 10;
int n, m, k;
int a[N];
bool good[N];
vector<int> g[N];

struct Node {
    int fax, fay, w;
};
vector<Node> stk;
int p[N * 2], rk[N * 2];

int find(int x)
{
    if (p[x] != x) return find(p[x]);
    return p[x];
}

bool merge(int u, int v) {
    int fax = find(u), fay = find(v);
    if(rk[fax] > rk[fay]) {
        swap(fax, fay);
    }
    if(fax != fay) {
        p[fax] = fay;
        stk.push_back({fax, fay, rk[fax] == rk[fay]});
        if(rk[fay] == rk[fax]) rk[fay]++;
        return true;
    }
    return false;
}

void undo() {
    while(stk.size()) {
        auto pa = stk.back(); stk.pop_back();
        int fax = pa.fax, fay = pa.fay, w = pa.w;
        p[fax] = fax;
        rk[fay] -= w;
    }
}

pair<int, int > e[N];
void solve() {
    for(int i = 0; i < N * 2; i++) p[i] = i;
    memset(good, true, sizeof good);
    
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    map<pair<int, int>, vector<pair<int, int>>> f;
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(a[u] > a[v]) {
            swap(u, v);
        }
        
        if(a[u] == a[v]) {
            if(!good[a[u]]) continue;
            if(find(u) == find(v)) {
                good[a[u]] = false;
                k--;
                continue;
            }
            merge(u, v + n);
            merge(v, u + n);

        } else {
            f[{a[u], a[v]}].push_back({u, v});
        }
    }

    stk.clear();
    ll res = (k + 0ll) * (k - 1) / 2;
    

    for(auto it = f.begin(); it != f.end(); it++) {
        auto pa = it -> first;
        auto edges = it -> second;

        for(auto e : edges) {
            int u = e.first, v = e.second;
            if(!good[a[u]] || !good[a[v]]) {
                break;
            }
            
            merge(u, v + n);
            merge(v, u + n);
            if(find(u) == find(v)) {
                res -= 1;
                break;
            }
        }
        undo();
    }
    
    cout << res << endl;

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
