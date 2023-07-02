#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int MAX = 60000 + 100;
const int MOD = 1e9 + 7;
const int N = 50010, M = 200010   ;
int n, m, len;
int a[N], ans[M];

vector<int> c, d;
map<int, int> f;

struct Node {
  int l, r;
  int e, o;
  int cnt;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(val < 0) {
      tree[id].cnt--;
      tree[id].e = 0;
      tree[id].o = 0;
    } else {
      tree[id].cnt++;
      tree[id].e = val;
      tree[id].o = 0;
    } 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  
  tree[id].cnt = tree[left].cnt + tree[right].cnt;
  if(tree[left].cnt % 2 == 0) {
    tree[id].o = (tree[left].o + tree[right].o) % MOD;
    tree[id].e = (tree[left].e + tree[right].e) % MOD;
  } else {
    tree[id].o = (tree[left].o + tree[right].e) % MOD;
    tree[id].e = (tree[left].e + tree[right].o) % MOD;
  }
  
 // cout << "update :" << l << "  " << r << "    |"  << tree[id].o << "  " << tree[id].e << "  " << tree[id].cnt << endl;
}

struct Info {
  int o, e, cnt;
};

Info query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].o, tree[id].e, tree[id].cnt};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    auto p1 = query(left, s, mid);
    auto p2 = query(right, mid + 1, e);
    
    //cout << l << "  " << "  "  << r << "  :" << p1.o << " " << p1.e << " " << p1.cnt << "   |" << p2.o << " " << p2.e << " " << p2.cnt << endl; 
     
    if(p1.cnt % 2 == 0) {
      return {(p1.o + p2.o) % MOD, (p1.e + p2.e) % MOD, p1.cnt + p2.cnt};
    } else {
      return {(p1.o + p2.e) % MOD, (p1.e + p2.o) % MOD, p1.cnt + p2.cnt};
    }
  }
}

struct Query
{
    int id, l, r;
}q[M];

void add(int x)
{
  update(0, f[x], x);
}

void del(int x) {
  update(0, f[x], -x);
}

int get(int x)
{
    return x / len;
}

bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

//complexity 
//if block : sqrt(n)
//r : n sqrt(n)
//l : m sqrt(n)
int main() {
    scanf("%d%d", &n, &m);
    vector<int> b;
    for (int i = 1; i <= n; i ++ ) {
      scanf("%d", &a[i]);
      b.push_back(a[i]);
    }

    sort(b.begin(), b.end());
    for(int i = 0; i < b.size(); i++) {
      f[b[i]] = i + 1;
    }
    tree[0] = {0, b.size() + 1, 0, 0, 0};
    build(0);


    len = max(1, (int)sqrt((double)n * n / m));
    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l + 1, r + 1};
    }
    
    sort(q, q + m, cmp);
    
    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++ )
    {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(a[ ++ i]);
        while (i > r) del(a[i -- ]);
        while (j < l) del(a[j ++ ]);
        while (j > l) add(a[ -- j]);
        
        auto p = query(0, 0, n);
        ans[id] = p.e;
        
    }
    
    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}
