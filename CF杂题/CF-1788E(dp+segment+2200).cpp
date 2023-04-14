
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mx;
};
Node tree1[MAX * 4];

void build(Node tree[], int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0};
  build(tree, id * 2 + 1);
  build(tree, id * 2 + 2);
}

void update(Node tree[], int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(tree, left, index, val);
  } else {
    update(tree, right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

int query(Node tree[], int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(tree, left, s, e);
  } else if(s >= mid + 1) {
      return query(tree, right, s, e);
  } else {
    return max(query(tree, left, s, mid), query(tree, right, mid + 1, e));
  }
}

const int N = 2e5 + 10;
int a[N], dp[N];
int n;
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    ll sum = 0;
    vector<pair<ll, int>> b;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        b.push_back({sum, i});
    }
    //离散化前缀和
    sort(b.begin(), b.end());
    map<ll, int> f;
    int id = 1;
    for(int i = 0; i < b.size(); i++) {
        int j = i;
        while(j < b.size() && b[j].first == b[i].first) {
            j++;
        }
        f[b[i].first] = id++;
        i = j - 1;
    }
    
    
    tree1[0] = {0, n, 0};
    build(tree1, 0);
    
    dp[0] = 0;
    int res = 0;
    sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        int ith = f[sum];
        
        int d = 0, more = n - i;
        if(sum >= 0) d = i;
        int best = query(tree1, 0, 0, ith);
        d = max(d, best - more);
        
        dp[i] = max(dp[i - 1], d);
        update(tree1, 0, ith, dp[i] + more);
    }
    
    
    cout << dp[n] << endl;
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

/*
5
3 -5 3 -100 0
*/
