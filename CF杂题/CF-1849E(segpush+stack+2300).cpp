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


const int MAX = 1e6 + 10;
struct Node {
  int l, r;
  int setTo, sum;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1, 0};
  tree[id * 2 + 2] = {mid + 1, r, -1, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].setTo = val;
    tree[id].sum = (val) * (r - l + 1);
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].setTo != -1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = -1;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }
  tree[id].sum = tree[left].sum + tree[right].sum;
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != -1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = -1;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");
const int N = 1e6 + 10;
int a[N];

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    tree[0] = {0, n, -1, 0};
    build(0);
    
    ll res = 0;
    vector<pair<int, int>> stk1, stk2;
    stk1.push_back({0, a[0]});
    stk2.push_back({0, a[0]});
    for(int i = 1; i < n; i++) {
        while(stk1.size() > 0 && a[i] >= stk1.back().second) {
            stk1.pop_back();
        }

        if(stk1.size() == 0) {
            update(0, 0, i, 1);
        } else {
            update(0, stk1.back().first + 1, i, 1);
        }
        stk1.push_back({i, a[i]});
        
        //////////////////////////////////////////////////////////////////

        while(stk2.size() > 0 && a[i] <= stk2.back().second) {
            stk2.pop_back();
        }

        if(stk2.size() == 0) {
            update(0, 0, i, 0);
        } else {
            update(0, stk2.back().first + 1, i, 0);
        }
        stk2.push_back({i, a[i]});

        res += query(0, 0, i);
    }

    cout << res << endl;
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
