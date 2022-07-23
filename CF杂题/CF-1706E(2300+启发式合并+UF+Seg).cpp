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

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

int n, m, q;
const int N = 1e5 + 10;
const int M = 2e5 + 10;
int a[N];
us<int> ver[N];

const int MAX = 1e5 + 100;
struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = a[l];
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, -1};
  tree[right] = {mid + 1, r, -1};
  build(left);
  build(right);
  tree[id].mx = max(tree[left].mx, tree[right].mx);
} 

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}

void solve() {
    scanf("%d%d%d", &n, &m, &q);
    ve<int> nums(n);
    for(int i = 0; i < n; i++) nums[i] = i;
    for(int i = 0; i < n; i++) {
      ver[i].clear(); ver[i].insert(i);
    }
    
    for(int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      int r1 = find(nums, u), r2 = find(nums, v);
      if(r1 == r2) continue;
      if(ver[r1].size() < ver[r2].size()) {
        nums[r1] = r2;
        for(int v : ver[r1]) {
          if(ver[r2].find(v - 1) != ver[r2].end()) {
            a[v - 1] = i + 1;
          }
          if(ver[r2].find(v + 1) != ver[r2].end()) {
            a[v] = i + 1;
          }
        } 
        for(int v : ver[r1]) {
          ver[r2].insert(v);
        }

      } else {
        nums[r2] = r1;

        for(int v : ver[r2]) {
          if(ver[r1].find(v - 1) != ver[r1].end()) {
            a[v - 1] = i + 1;
          }
          if(ver[r1].find(v + 1) != ver[r1].end()) {
            a[v] = i + 1;
          }
        }

        for(int v : ver[r2]) {
          ver[r1].insert(v);
        }
      }
      //cout << i << endl;
    }
    
    /*cout << endl;
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }cout << endl;*/


    tree[0] = {0, n - 2, -1};
    build(0);
    for(int i = 0; i < q; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      l--; r--;
      if(l == r) {
        printf("0 ");
        continue;
      }
      int ans = query(0, l, r - 1);
      printf("%d ",ans);
    }
    printf("\n");
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
