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

const int MAX = 4e5 + 1000;
struct Node {
  int l, r;
  int val = 0; ll sum = 0;
  int cnt = 0;
} tree[MAX * 4], cntTree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
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
    tree[id].val += val; 
    tree[id].sum += val; 
    tree[id].cnt ++;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].sum = (tree[left].sum + tree[right].sum);
  tree[id].cnt = (tree[left].cnt + tree[right].cnt);
}

ll query(int id, int s, int e) { // query sum from [0 : l]
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

int query1(int id, int s, int e) { // query sum from [0 : l]
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].cnt;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return query1(left, s, mid) + query1(right, mid + 1, e);
  }
}

const int N = 2e5 + 10;
int p[N];
int cnt[N];
ll sums[N], tot[N];
void solve() {
    ll res = 0;
    int n;
    string s;
    cin >> n >> s;    
    
    /*
    //brute force
    ll res = 0;
    for(int i = 0; i < n; i++) {
        int all = 0, p = 0;
        int mn = 0;
        for(int j = i; j < n; j++ ) {
            if(s[i] == '(') all++;
            else all--;
            p = min(p, all);
            res += (-p + max(0, all));
        }
    }*/
    
    int lim = n;
    tree[0] = {-lim - 10, lim + 10, 0, 0};
    build(0);
    update(0, 0, 0);
    
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') sum++;
        else sum--;
        
        p[i] = sum;
        int cnt = query1(0, -lim - 10, sum);
        ll tot =  query(0, -lim - 10, sum);
        
        //cout << sum << "  " << cnt << "  " << tot << endl;
        
        res += (sum * cnt - tot);
        update(0, sum, sum);
    }
    
    /*cout << endl;
    for(int i = 0; i < n; i++) cout << p[i] << "  ";
    cout << endl;
    cout << res << endl;*/
    
    for(int i = 0; i <= n; i++) {
        sums[i] = 0;
        cnt[i] = 0;
        tot[i] = 0;
    } 
   
    vector<int> stk;
    sum = 0;
    cnt[0] = 1;
    sums[0] = 0;
    p[0] = 0; 
    
    stk.push_back(0);
    for(int i = 1; i <= n; i++) {
        if(s[i - 1] == '(') {
            sum--;
        } else {
            sum++;
        }
        p[i] = sum;
        cnt[i] = 1;
        sums[i] = sum;
        while(stk.size() > 0 && sum >= p[stk.back()]) {
            int idx = stk.back(); stk.pop_back();
            cnt[i] += cnt[idx];
            sums[i] += sums[idx];
        }
        if(stk.size()) {
            tot[i] += tot[stk.back()];
        }
        tot[i] += (((p[i] + 0ll) * cnt[i]) - sums[i]);
        res += tot[i];
        stk.push_back(i);
    }
    
    /*for(int i = 0; i <= n; i++) {
        cout << p[i] << " ";
    } cout << endl;
    
    for(int i = 0; i <= n; i++) {
        cout << sums[i] << " ";
    } cout << endl;
    
    for(int i = 0; i <= n; i++) {
        cout << tot[i] << " ";
    } cout << endl;*/
    
    printf("%lld\n", res);
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
