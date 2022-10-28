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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e5 + 10, mod = 95542721;
int a[N], s[N][48];
int n, m;

const int MAX = 1e5 + 10;
struct Node {
  int l, r, setTo;
  int p[48];
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    for(int i = 0; i < 48; i++) {
        tree[id].p[i] = s[l][i];
    }
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, 0};
  tree[right] = {mid + 1, r, 0};
  build(left);
  build(right);

  for(int i = 0; i < 48; i++) {
    tree[id].p[i] = tree[left].p[i] + tree[right].p[i];
    tree[id].p[i] %= mod;
  }
}


void update(int id, int s, int e, int val) { 
    int l = tree[id].l, r = tree[id].r;
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(l == s && r == e) {
        tree[id].setTo += val;
        tree[id].setTo %= 48;
        int sto = tree[id].setTo;

        if(l == r) {
            tree[id].setTo = 0;
            int pp[48];
            for(int i = 0; i < 48; i++) {
                pp[i] = tree[id].p[(i + sto) % 48];
            }
            for(int i = 0; i < 48; i++) {
                tree[id].p[i] = pp[i];
            }
            return;
        }

        for(int i = 0; i < 48; i++) {
            tree[id].p[i] = tree[left].p[(i + sto) % 48] + tree[right].p[(i + sto) % 48];
            tree[id].p[i] %= mod;
        }
        return;
    }


    if(tree[id].setTo != 0) {
        update(left, tree[left].l, tree[left].r, tree[id].setTo);
        update(right, tree[right].l, tree[right].r, tree[id].setTo);
        tree[id].setTo = 0;
    }

    if(e <= mid) {
        update(left, s, e, val);
    } else if(s >= mid + 1) {
        update(right, s, e, val);
    } else {
        update(left, s, mid, val);
        update(right, mid + 1, e, val);
    }
    
    for(int i = 0; i < 48; i++) {
        tree[id].p[i] = tree[left].p[i] + tree[right].p[i];
        tree[id].p[i] %= mod;
    }
 
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].p[0];
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return (query(left, s, mid) + query(right, mid + 1, e)) % mod;
  }
}


void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++) {
        s[i][0] = a[i];
        for(int j = 1; j < 48; j++) {
            ll x = s[i][j - 1];
            ll t = ((x * x) % mod * x) % mod;
            s[i][j] = t;
        }
    }


    tree[0] = {0, n - 1, 0};
    build(0);

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) { //query
            int res = query(0, l - 1, r - 1);
            printf("%d\n", res);
        } else { //update
            update(0, l - 1, r - 1, 1);
        }
    }
} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

