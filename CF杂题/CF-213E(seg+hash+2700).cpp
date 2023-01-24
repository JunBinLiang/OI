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

const int N = 2e5 + 10;
int a[N], b[N], pos[N];
int n, m;
int base = 10, mod = 1e9 + 7;
ll p[N];
int res = 0;

struct Node {
  int l, r;
  ll setTo, ha;
} tree[N * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 1, 0};
  tree[id * 2 + 2] = {mid + 1, r, 1, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, ll val, int o) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    if(o == 0) {
        tree[id].ha = val;
        tree[id].setTo = 1;
    } else {
        tree[id].setTo *= val;
        tree[id].setTo %= mod;
        tree[id].ha *= val;
        tree[id].ha %= mod;
    }
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].setTo != 1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, 1);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, 1);
    tree[id].setTo = 1;
  }

  if(e <= mid) {
    update(left, s, e, val, o);
  } else if(s >= mid + 1) {
    update(right, s, e, val, o);
  } else {
    update(left, s, mid, val, o);
    update(right, mid + 1, e, val, o);
  }
  tree[id].ha = (tree[left].ha + tree[right].ha) % mod;
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].ha;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != 1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, 1);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, 1);
    tree[id].setTo = 1;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

namespace Fenwick {
  const int SIZE = 200000 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

ll inve(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}


void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
        pos[b[i]] = i;
    }
    
    tree[0] = {0, m, 0, 0};
    build(0);
    Fenwick :: init();
    ll inv = inve(base, mod);

    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = p[i - 1] * base;
        p[i] %= mod;
    }


    //2 4 1 3
    //3 5 2 4
    ll h = 0, add = 0;
    for(int i = 1; i <= n; i++) {
        h = h * base + a[i];
        h %= mod;
    }

    for(int i = 0; i < n; i++) {
        add += p[i];
        add %= mod;
    }
    
    for(int i = 1; i <= n; i++) {
        int idx = pos[i];
        update(0, 0, idx - 1, base, 1);
        int cnt = 0;
        if(idx + 1 <= m) {
            cnt = Fenwick :: query(idx + 1, m);
        }
        
        ll v = (p[cnt] * i) % mod;
        update(0, idx, idx, v, 0);
        Fenwick :: update(idx, 1);
    }

    for(int i = 1; i <= m; i++) {
        int lo = i, hi = i + n - 1;
        if(hi > m) break;

        if(query(0, 0, m) == h) {
            res++;
        }
        h += add;
        h %= mod;

        //remove cur
        int idx = pos[i];
        Fenwick :: update(idx, -1);
        update(0, idx, idx, 0, 0);
        update(0, 0, idx - 1, inv, 1);
        
        //add next
        if(i + n <= m) {
            int nxt = pos[i + n];
            int cnt = 0;
            if(nxt + 1 <= m) {
                cnt = Fenwick :: query(nxt + 1, m);
            }
            ll v = (p[cnt] * (i + n)) % mod;
            update(0, 0, nxt - 1, base, 1);
            update(0, nxt, nxt, v, 0);
            Fenwick :: update(nxt, 1);
        }
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

