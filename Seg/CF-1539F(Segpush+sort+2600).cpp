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

const int MAX = 200000 + 10;
struct Node {
  int l, r;
  int setTo = 0, mx = 0, mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = tree[id].mn = l;
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, 0, 0};
  tree[right] = {mid + 1, r, 0, 0};
  build(left);
  build(right);
  tree[id].mx = max(tree[left].mx, tree[right].mx);
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

void update(int id, int s, int e, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].setTo += val;
    tree[id].mx += val; 
    tree[id].mn += val; 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

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
  tree[id].mx = max(tree[left].mx, tree[right].mx);
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return max(query1(left, s, mid), query1(right, mid + 1, e));
  }
}

int query2(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }
  if(e <= mid){
      return query2(left, s, e);
  } else if(s >= mid + 1) {
      return query2(right, s, e);
  } else {
    return min(query2(left, s, mid), query2(right, mid + 1, e));
  }
}

const int N = 2e5 + 10;
vector<pair<int, int>> a;
int res[N];
bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.first < p2.first;
}


void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back({x, i});
    }
    memset(res, 0, sizeof res);
    sort(a.begin(), a.end(), COMP);   

    tree[0] = {0, n, 0, 0};
    build(0); 

    for(int i = 0; i < a.size(); i++) {
        int j = i;        
        while(j < a.size() && a[j].first == a[i].first) {
            j++;
        }

        for(int k = i; k < j; k++) {
            int idx = a[k].second;
            int mx = query1(0, idx, n);
            res[idx] = max(res[idx], (mx) / 2);
            int mn = query2(0, 0, idx - 1);
            res[idx] = max(res[idx], (mx - mn) / 2);
        }

        for(int k = i; k < j; k++) {
            int idx = a[k].second;
            update(0, idx, n, -2);
        }
        i = j - 1;
    }


    tree[0] = {0, n, 0, 0};
    build(0); 
    reverse(a.begin(), a.end());
    for(int i = 0; i < a.size(); i++) {
        int j = i;
        while(j < a.size() && a[j].first == a[i].first) {
            j++;
        }

        for(int k = i; k < j; k++) {
            int idx = a[k].second;
            int mx = query1(0, idx, n);
            res[idx] = max(res[idx], (mx - 1) / 2);
            int mn = query2(0, 0, idx - 1);
            res[idx] = max(res[idx], (mx - mn - 1) / 2);
        }

        for(int k = i; k < j; k++) {
            int idx = a[k].second;
            update(0, idx, n, -2);
        }

        i = j - 1;
    }

    

    for(int i = 1; i <= n; i++) printf("%d ", res[i]); 
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
