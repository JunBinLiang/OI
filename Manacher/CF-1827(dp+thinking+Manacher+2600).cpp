
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
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

const int N = 5e5 + 10;
ll dp[N];
vector<int> manacher_odd(string s) {
    int n = s.length();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

const int MAX = 5e5 + 10;
const int INF = 1e9;
struct Node {
  int l, r;
  ll setTo, mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1, INF};
  tree[id * 2 + 2] = {mid + 1, r, -1, INF};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    if(tree[id].setTo == -1)
        tree[id].setTo = val;
    else {
        tree[id].setTo = min(tree[id].setTo, val);
    }
    tree[id].mn = min(tree[id].mn, val);
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
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
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
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

void solve() {
    int n;
    string s;
    ll res = 0;
    cin >> n >> s;

    string t = "";
    for(int i = 0; i < n; i++) {
        t += s[i];
        if(i < n - 1) {
            t += "|";
        }
    }

    for(int i = 0; i <= n; i++) dp[i] = 0;
    tree[0] = {0, n, -1, INF};
    build(0);
    
    
    vector<int> v = manacher_odd(t);
    /*for(char c : t) {
        cout << c << " ";
    }
    cout << endl << endl;
    
    for(int x : v) {
        cout << x << " ";
    }
    cout << endl;*/
    
    for(int i = 1; i < v.size(); i += 2) {
        int len = v[i];
        if(len < 2) continue;
        int L = (i - len + 1);
        if(L % 2 == 1) {
            L++;
        }
        L /= 2;
        int R = (i - 1) / 2;
        update(0, L, R, R);
    }
    
    //cout << query(0, 0, 0) << endl;
    
    //cout << endl;

    for(int i = n - 1; i >= 0; i--) {
        int to = query(0, i, i);
        if(to == INF) {
            dp[i] = 0;
        } else {
            int len = (to - i + 1) * 2;
            int nxt = i + len - 1;
            dp[i] = 1 + dp[nxt + 1];
        }
    }

    for(int i = 0; i < n; i++) res += dp[i];
    cout << res << endl;
}

int main()
{   
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
