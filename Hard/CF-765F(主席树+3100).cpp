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
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

struct Q{
    int l, r, idx;
};

bool COMP1(const Q& p1, const Q& p2) {
    return p1.r < p2.r;
}

bool COMP2(const Q& p1, const Q& p2) {
    return p1.l > p2.l;
}

const int N = 1e5 + 10, M = 3e5 + 10;
const int INF = 2e9;
int n, m;
int a[N], l[N];
int ans[M], root[N];
vector<Q> q;

namespace MinSeg {
    const int MAX = 4e5 + 100;
    struct Node {
        int l, r;
        int mn;
    } tree[MAX * 16];

    void build(int id) {
        int l = tree[id].l, r = tree[id].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        tree[id * 2 + 1] = {l, mid, INF};
        tree[id * 2 + 2] = {mid + 1, r, INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val) { 
        int l = tree[id].l, r = tree[id].r;
        if(l == r) {
            tree[id].mn = min(tree[id].mn, val);  
            return;
        }

        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        tree[id].mn = min(tree[left].mn, tree[right].mn);
    }

    int query(int id, int s, int e) {
        int l = tree[id].l, r = tree[id].r;
        if(l == s && r == e){
            return tree[id].mn;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return min(query(left, s, mid), query(right, mid + 1, e));
        }
    }
}

namespace PresidentTree {
    const int N = 2e5 + 100;
    struct Node {
        int l, r;
        int lid, rid;
        int mx;
    } tree[N * 16];

    
    int idx = 0;
    void build(int id) {
        int l = tree[id].l, r = tree[id].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        int idx1 = idx;
        int idx2 = idx + 1;
        idx += 2;
        tree[id].lid = idx1;
        tree[id].rid = idx2;
        tree[idx1] = {l, mid, -1, -1, -1};
        tree[idx2] = {mid + 1, r,-1, -1, -1};
        build(idx1);
        build(idx2);
    }

    void update(int preId, int curId, int index, int val) {
        int l = tree[curId].l, r = tree[curId].r;
        if(l == r) {
            tree[curId].mx = max(tree[curId].mx, val);
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {//update left
            tree[curId].rid = tree[preId].rid;
            tree[idx] = {tree[tree[preId].lid].l, tree[tree[preId].lid].r, -1, -1, -1};
            tree[curId].lid = idx;
            idx++;
            update(tree[preId].lid, tree[curId].lid, index, val);
        } else {//update right
            tree[curId].lid = tree[preId].lid;    
            tree[idx] = {tree[tree[preId].rid].l, tree[tree[preId].rid].r, -1, -1, -1};
            tree[curId].rid = idx;
            idx++;
            update(tree[preId].rid, tree[curId].rid, index, val);
        }
        tree[curId].mx = max(tree[tree[curId].lid].mx, tree[tree[curId].rid].mx);
    }

    int query(int id, int s, int e) {
        int l = tree[id].l, r = tree[id].r;
        if(l == s && r == e){
            return tree[id].mx;
        }
        int mid = l + (r - l) / 2;
        int left = tree[id].lid, right = tree[id].rid;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return max(query(left, s, mid), query(right, mid + 1, e));
        }
    }
}

void solve() {
    scanf("%d", &n);
    vector<int> b;
    for(int i = 1; i <= n; i++) {  
        scanf("%d", &a[i]);
        b.push_back(a[i]);
    }
    //离散化
    sort(b.begin(), b.end());
    int id = 0; 
    unordered_map<int, int> f;
    for(int i = 0; i < b.size(); i++) {
        int j = i;
        while(j < b.size() && b[j] == b[i]) {
            j++;
        }
        f[b[i]] = id++;
        i = j - 1;
    }

    vector<int> stk;
    memset(l, -1, sizeof l);
    for(int i = 1; i <= n; i++) {
        while(stk.size() > 0 && a[i] < a[stk.back()]) stk.pop_back();
        if(stk.size() > 0) {
            l[i] = stk.back();
        }
        stk.push_back(i);
    }
    

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        ans[i] = INF;
        q.push_back({l, r, i});
    }
    sort(q.begin(), q.end(), COMP1);
    

    set<int> s;
    MinSeg :: tree[0] = {1, n, INF};
    MinSeg :: build(0);
    PresidentTree :: tree[0] = {0, n, -1, -1, -1};
    PresidentTree :: idx++;
    PresidentTree :: build(0);
    root[0] = 0;
    
    int last = 0;
    for(int i = 0; i < q.size(); i++) {
        int j = i;
        for(int k = last + 1; k <= q[i].r; k++) {
            int v = a[k];
            if(l[k] == -1) {
                s.insert(a[k]);
                root[k] = PresidentTree :: idx;
                PresidentTree :: tree[root[k]] = {0, n, -1, -1, -1};
                PresidentTree :: idx++;
                PresidentTree :: update(root[k - 1], root[k], f[a[k]], k);
                continue;
            } else {
                int lastIdx = l[k];
                MinSeg :: update(0, lastIdx, a[k] - a[lastIdx]);
                
                int pR = f[a[k]];
                while(lastIdx != -1 && a[lastIdx] != a[k]) {
                    int mid = a[lastIdx] + (a[k] - a[lastIdx]) / 2;;
                    auto it = s.upper_bound(mid - 1);
                    if(it == s.end()) {
                        break;
                    } else {
                        int v = *it;
                        int pL = f[v];
                        if(pL <= pR) {
                            int idxx = PresidentTree :: query(root[lastIdx - 1], pL, pR);
                            lastIdx = idxx;
                            if(lastIdx != -1) {
                                MinSeg :: update(0, lastIdx, a[k] - a[lastIdx]);
                            }
                        } else {
                            break;
                        }
                    }
                }
                s.insert(a[k]);
                root[k] = PresidentTree :: idx;
                PresidentTree :: tree[root[k]] = {0, n, -1, -1, -1};
                PresidentTree :: idx++;
                PresidentTree :: update(root[k - 1], root[k], f[a[k]], k);
            }
        }

        while(j < q.size() && q[j].r == q[i].r) {
            int l = q[j].l, r = q[j].r, idx = q[j].idx;
            ans[idx] = min(ans[idx], MinSeg :: query(0, l, n));
            j++;
        }
        last = q[i].r;
        i = j - 1;
    }


    stk.clear();
    memset(l, -1, sizeof l);
    for(int i = 1; i <= n; i++) {
        while(stk.size() > 0 && a[i] >= a[stk.back()]) stk.pop_back();
        if(stk.size() > 0) l[i] = stk.back();
        stk.push_back(i);
    }

    s.clear();
    MinSeg :: tree[0] = {1, n, INF};
    MinSeg :: build(0);
    PresidentTree :: idx = 0;
    PresidentTree :: tree[0] = {0, n, -1, -1, -1};
    PresidentTree :: idx++;
    PresidentTree :: build(0);
    root[0] = 0;
    last = 0;

    for(int i = 0; i < q.size(); i++) {
        int j = i;
        for(int k = last + 1; k <= q[i].r; k++) {
            int v = a[k];
            if(l[k] == -1) {
                s.insert(a[k]);
                root[k] = PresidentTree :: idx;
                PresidentTree :: tree[root[k]] = {0, n, -1, -1, -1};
                PresidentTree :: idx++;
                PresidentTree :: update(root[k - 1], root[k], f[a[k]], k);
                continue;
            } else {
                int lastIdx = l[k];
                MinSeg :: update(0, lastIdx, a[lastIdx] - a[k]);
                
                int pR = f[a[k]];
                while(lastIdx != -1 && a[lastIdx] != a[k]) {
                    int mid = a[k] + (a[lastIdx] - a[k]) / 2;
                    auto it = s.upper_bound(mid - 1);
                    if(it == s.end()) {
                        break;
                    } else {
                        if(*it != mid) {
                            if(it == s.begin()) break;
                            it--;
                        }
                        int v = *it;
                        int pL = f[v];
                        if(pR <= pL) {
                            int idxx = PresidentTree :: query(root[lastIdx - 1], pR, pL);
                            lastIdx = idxx;
                            if(lastIdx != -1) {
                                MinSeg :: update(0, lastIdx, a[lastIdx] - a[k]);
                            }
                        } else {
                            break;
                        }
                    }
                }
                s.insert(a[k]);
                root[k] = PresidentTree :: idx;
                PresidentTree :: tree[root[k]] = {0, n, -1, -1, -1};
                PresidentTree :: idx++;
                PresidentTree :: update(root[k - 1], root[k], f[a[k]], k);
            }
        }

        while(j < q.size() && q[j].r == q[i].r) {
            int l = q[j].l, r = q[j].r, idx = q[j].idx;
            ans[idx] = min(ans[idx], MinSeg :: query(0, l, n));
            j++;
        }
        last = q[i].r;
        i = j - 1;
    }


    for(int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
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
