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



const int N = 2e5 + 10, INF = 1e9, M = 5e5 + 10;
int n, m, k;

struct Info {
    int u, val, t;
    bool operator <(const Info& other) {
        return val < other.val;
    }
};

struct Task {
    int r1, r2, cnt;
} tasks[M];


pair<int, int> e[M], q[M];
vector<Info> comp[N];
vector<int> vec[N];
int a[N], p[N], pos[N], rk[N], sz[N];
bool vis[M], use[N], de[M];

int find(int x) {
    if(x != p[x]) {
        return find(p[x]);
    }
    return p[x];
}



void solve() {
    memset(de, false, sizeof de);
    
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++) {
        scanf("%d%d", &e[i].first, &e[i].second);
        if(e[i].first > e[i].second) swap(e[i].first, e[i].second);
    }
    
    for(int i = 0; i < k; i++) {
        scanf("%d%d", &q[i].first, &q[i].second);
        if(q[i].first == 2) {
            de[q[i].second] = true;
        }
    }
    
    //UF for non delete edge
    for(int i = 1; i <= n; i++) p[i] = i, sz[i] = 1, rk[i] = 1;
    
    for(int i = 1; i <= m; i++) {
        if(!de[i]) {
            int u = e[i].first, v = e[i].second;
            int r1 = find(u), r2 = find(v);
            if(rk[r1] > rk[r2]) {
                swap(r1, r2);
            }
            
            if(r1 == r2) {
                continue;
            }
            
            p[r1] = r2;
            sz[r2] += sz[r1];
            if(rk[r1] == rk[r2]) rk[r2]++;
        }
    }
    
    
    for(int i = 1; i <= n; i++) {
        int r = find(i);
        comp[r].push_back({i, a[i], INF});
        vec[r].push_back(i);
        pos[i] = r;
    }
    
    
    /*for(int i = 1; i <= n; i++) {
        if(vec[i].size() == 0) continue;
        cout << i << endl;
        for(int x : vec[i]) cout << x << " ";
        cout << endl;
    }*/

    //reverse order merge
    memset(vis, false, sizeof vis);
    memset(use, false, sizeof use);
    for(int i = k - 1; i >= 0; i--) {
        if(q[i].first != 2) continue;
        int ith = q[i].second;
        int u = e[ith].first, v = e[ith].second;
        int r1 = find(u), r2 = find(v);
        if(r1 == r2) {
            continue;
        }
        
        if(comp[r1].size() > comp[r2].size()) {
            swap(r1, r2);
        }
        
        p[r1] = r2;
        sz[r2] += sz[r1];

        for(int j = 0; j < comp[r1].size(); j++) {
            comp[r2].push_back({comp[r1][j].u, comp[r1][j].val, i});
        }
        
        for(int j = 0; j < vec[r1].size(); j++) {
            vec[r2].push_back(vec[r1][j]);
            pos[vec[r1][j]] = r2;
        }
        vis[i] = true;
        tasks[i] = {r1, r2, (int)(vec[r1].size())};
    }
    
    for(int i = 1; i <= n; i++) {
        sort(comp[i].begin(), comp[i].end());
    }
    
    for(int i = 0; i < k; i++) {
        int op = q[i].first, u = q[i].second;
        if(op == 1) {
            int ith = pos[u];
            int res = 0;
            while(comp[ith].size() > 0) {
                auto& info = comp[ith].back();
                if(info.t < i || use[info.val]) {
                    comp[ith].pop_back();
                } else {
                    break;
                }
            }
            if(comp[ith].size() > 0) {
                res = comp[ith].back().val;
                use[comp[ith].back().val] = true;
            }
            printf("%d\n", res);
        } else {
            if(!vis[i]) continue;
            int r1 = tasks[i].r1, r2 = tasks[i].r2, cnt = tasks[i].cnt;
            //r1 -> r2
            while(cnt--) {
                int last = vec[r2].back(); vec[r2].pop_back();
                pos[last] = r1;
            }
        }
    }
}

int main() {
    solve();
    return 0;
}
