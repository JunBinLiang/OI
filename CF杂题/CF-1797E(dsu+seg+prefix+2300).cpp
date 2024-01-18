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
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MAX = 1e5 + 100;

struct Node {
  int l, r;
  int mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 1000000000};
  tree[id * 2 + 2] = {mid + 1, r, 1000000000};
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

namespace Fenwick {
  const int SIZE = 100000 + 100;
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

const int N = 5e6 + 10;
int primes[N], cnt;
bool st[N];
int phi[N];
void init(int n)
{
  phi[1] = 1;
  for (int i = 2; i <= n; i ++ ) {
    if (!st[i])
    {
        primes[cnt ++ ] = i;
        phi[i] = i - 1;
    }
    for (int j = 0; primes[j] * i <= n; j ++ )
    {
        st[i * primes[j]] = true;
        if (i % primes[j] == 0)
        {
            phi[i * primes[j]] = phi[i] * primes[j];
            break;
        }
        phi[i * primes[j]] = phi[i] * (primes[j] - 1);
    }
  }
}

const int INF = 1e9, M = 1e5 + 10;
int p[M][26]; int nums[M * 26];
map<int, int> f;
map<int, int> maps[M];

int find(int u) {
  return nums[u] == u ? u : nums[u] = find(nums[u]); 
}

void solve() {
    init(N - 1); 
    Fenwick :: init();
    memset(p, 0, sizeof p);
    for(int i = 0; i < M * 26; i++) nums[i] = i;

    int n, m;
    scanf("%d%d", &n, &m);

    tree[0] = {0, n, 1000000000};
    build(0);
    
    V<int> a(n);
    FOR(i, 0, n) {
      scanf("%d", &a[i]);
      int v = a[i];
      update(0, i, v); //init value
      V<int> b;
      while(v != 1) {
        b.push_back(v);
        v = phi[v];
      }
      b.push_back(v);
      if(b.size() > 1) {
        f[i] = b.size() - 1;
      }

      FOR(j, 0, b.size()) {
        p[i][j] = j;
        maps[i][b[j]] = j;
      }

      if(i > 0) {
        FOR(j, 0, b.size()) {
          int x = b[j];
          if(maps[i - 1].find(x) != maps[i - 1].end()) {
            int preindex = maps[i - 1][x];
            int u = i * 25 + j, v = (i - 1) * 25 + preindex;
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) nums[r1] = r2;
            p[i][j] += p[i - 1][preindex];
          }
        }
      }
    }
    

    FOR(i, 0, m) {
      int op, l, r;
      scanf("%d%d%d", &op, &l, &r);
      l--; r--;
      if(op == 1) { //can brute force
        auto it = f.upper_bound(l - 1);
        while(it != f.end() && it -> first <= r) {
          int index = it -> first;
          a[index] = phi[a[index]];
          update(0, index, a[index]);
          Fenwick :: update(index, 1);
          f[index]--;
          if(f[index] == 0) f.erase(index);
          it = f.upper_bound(index);
        }
        
      } else {
        if(l == r) {
          printf("0\n");
          continue;
        }
        
        int v = a[r], count = Fenwick :: query(r, r);
        int res = INF, totalDecrease = Fenwick :: query(l, r);
        while(v != 1) {
          int minval = query(0, l, r);
          if(v <= minval && maps[l].find(v) != maps[l].end()) {
            int index = maps[l][v];
            int u = r * 25 + count, uu = l * 25 + index;
            int r1 = find(u), r2 = find(uu);
            if(r1 == r2) {
              if(l == 0) {
                res = min(res, (p[r][count]) - totalDecrease);
              } else {
                if(maps[l - 1].find(v) != maps[l - 1].end()) {
                  res = min(res, (p[r][count] - p[l - 1][maps[l - 1][v]]) - totalDecrease);
                } else {
                  res = min(res, (p[r][count]) - totalDecrease);
                }
              }
            }
          }
          v = phi[v];
          count++;
        }
        //case for all turn to 1
        if(l == 0) {
          res = min(res, (p[r][count]) - totalDecrease);
        } else {
          res = min(res, (p[r][count] - p[l - 1][maps[l - 1][1]]) - totalDecrease);
        }
        printf("%d\n", res);
      }
    } 
}
    

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
