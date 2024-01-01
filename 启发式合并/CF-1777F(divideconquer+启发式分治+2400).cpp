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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back

const int N = 2e5 + 10;
int a[N], p[N];

int tr[N * 32 * 10][2];
int cnt[N * 32 * 20];
int id = 0, res = 0;
void add(int root, int n) {
    int u = root;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b] == -1) {
            tr[u][b] = id++;
        }
        u = tr[u][b];
        cnt[u]++;
    }
    //cout << "add " << root << endl;
}

void del(int root, int n) {
    int u = root;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        u = tr[u][b];
        cnt[u]--;
    }
}

int find(int root, int n) {
    int u = root;
    int res = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b ^ 1] != -1 && cnt[tr[u][b ^ 1]] > 0) {
            res += (1 << i);
            u = tr[u][b ^ 1];
        } else {
            u = tr[u][b];
        }
    }
    return res;
}


const int MAX = 200000 + 100;
struct Node {
  int l, r;
  int mx, mxIdx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mxIdx = l;
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  if(tree[left].mx > tree[right].mx) {
    tree[id].mx = tree[left].mx;
    tree[id].mxIdx = tree[left].mxIdx;
  } else {
    tree[id].mx = tree[right].mx;
    tree[id].mxIdx = tree[right].mxIdx;
  }
}

pair<int, int> query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].mx, tree[id].mxIdx} ;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    auto p1 = query(left, s, mid), p2 = query(right, mid + 1, e);
    if(p1.first > p2.first) return p1;
    else return p2;
  }
}


void divide(int root, int L, int R) {
    if(L >= R) {
        return;
    }
    auto pa = query(0, L, R);
    int maxV = pa.first;
    int maxIdx = pa.second;
    //[L : maxIdx - 1]   [maxIdx : R]
    int newroot = id++;

    if(maxIdx - L <= R - maxIdx + 1) {
        for(int i = L - 1; i <= maxIdx - 1; i++) {
            add(newroot, p[i]);
            del(root, p[i]);
        }
        for(int i = L - 1; i <= maxIdx - 1; i++) {
            res = max(res, find(root, p[i] ^ maxV));
        }
        divide(newroot, L, maxIdx - 1);
        divide(root, maxIdx + 1, R);
    } else {
        for(int i = maxIdx; i <= R; i++) {
            add(newroot, p[i]);
            del(root, p[i]);
        }
        
        for(int i = maxIdx; i <= R; i++) {
            res = max(res, find(root, p[i] ^ maxV));
        }
        divide(root, L, maxIdx - 1);
        divide(newroot, maxIdx + 1, R);
    }
    

}


void solve() {
    int n;
    scanf("%d", &n);

    //init
    id = 0;
    res = 0;
    p[0] = 0;

    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        p[i] = a[i];
        p[i] ^= p[i - 1];
    } 

    tree[0] = {0, n, 0, 0};
    build(0);
    for(int i = 1; i <= n; i++) {
        update(0, i, a[i]);
    }

    int root = id++;
    for(int i = 0; i <= n; i++) {
        add(root, p[i]);
    }
    
    divide(0, 1, n);
    
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        mx = max(mx, a[i]);
        res = max(res, p[i] ^ mx);
    }
    
    cout << res << endl;

    //clear the trie
    for(int i = 0; i <= id + 1; i++) {
        tr[i][0] = tr[i][1] = -1;
        cnt[i] = 0;
    }
}

int main()
{
    memset(tr, -1, sizeof tr);
    memset(cnt, 0, sizeof cnt);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
