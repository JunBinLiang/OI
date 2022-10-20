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

const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mn, mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 500000, -1};
  tree[id * 2 + 2] = {mid + 1, r, 500000, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = min(tree[id].mn, val);  
    tree[id].mx = max(tree[id].mx, val);  
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
  tree[id].mx = max(tree[left].mx, tree[right].mx);
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

int query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return max(query1(left, s, mid), query1(right, mid + 1, e));
  }
}

struct Q {
    int idx, i, v;
};

const int N = 2e5 + 10;
int a[N], to[N], dp[N], cnt[N];
ll p[N];
ll sums[N];
int n;
ll sum = 0;

ll get(int l, int r) {
    if(l > r) return 0;
    return p[r] - p[l - 1];
}

void solve() {
    scanf("%d", &n);
    memset(dp, 0, sizeof dp);
    cnt[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        to[i] = max(1, i - a[i] + 1);
        if(i == 1) {
            dp[i] = to[i];
        } else {
            dp[i] = max(dp[i - 1], to[i]);
        }
        cnt[i] = i - dp[i] + 1;
        sum += (i - dp[i] + 1);
    }
    
    vector<int> stk;
    for(int i = n; i >= 0; i--) {
        while(stk.size() > 0 && to[i] >= to[stk.back()]) stk.pop_back();
        if(stk.size() > 0) {
            int idx = stk.back() - 1;
            ll count = idx - i + 1;
            sums[i] = (1 + count) * count / 2;
            
            if(idx + 1 <= n) {
                sums[i] += sums[idx + 1];    
            }
            sums[i] += (count * (i - to[i]));
        } else {
            ll count = n - i + 1;
            sums[i] = (1 + count) * count / 2;
            sums[i] += (count * (i - to[i]));
        }
        stk.push_back(i);
    }
    

    tree[0] = {0, n, 500000, -1};
    build(0);
    for(int i = 1; i <= n; i++) {
        update(0, i, max(1, i - a[i] + 1));
    }

    p[0] = cnt[0];
    for(int i = 1; i <= n; i++) p[i] = p[i - 1] + cnt[i];
    
    int m;
    scanf("%d", &m);
    for(int j = 0; j < m; j++) {
        int i, v;
        scanf("%d%d", &i, &v);
        ll t = sum;
        t -= cnt[i];
        int to = max(1, i - v + 1);
        int dpi = -1;
        if(i == 1) dpi = to;
        else dpi = max(dp[i - 1], to);
        int x = dpi;
        t += (i - x + 1);
        int l = i + 1, r = n;
        int pos = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;  
            int mx = query1(0, i + 1, mid);
            if(mx <= x) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        t -= get(i + 1, n);
        
        if(pos != -1) {
            ll first = i + 1, last = pos;
            ll count = (last - first) + 1;
            ll add = ((1 + (1 + count - 1)) * count / 2) + count * (first - x);
            t += add;
            if(pos + 1 <= n) {
                t += sums[pos + 1];
            }
        } else {
            t += sums[i + 1];
        }
        printf("%lld\n", t);
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
