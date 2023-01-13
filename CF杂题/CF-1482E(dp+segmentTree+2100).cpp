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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MAX = 300000 + 100;
const int N = 3e5 + 10;
const ll INF = 10000000000000000ll;

struct Node {
  int l, r;
  ll mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -INF};
  tree[id * 2 + 2] = {mid + 1, r, -INF};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

ll query(int id, int s, int e) {
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


int a[N];
int b[N];
ll val[N];
ll dp[N];
int n;
ll res = -10000000000000000ll;

void del(map<ll, int>& f, int k) {
    f[k]--;
    if(f[k] == 0) {
        f.erase(k);
    }
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    for(int i = 0; i < N; i++) {
        dp[i] = -INF;
    }

    tree[0] = {0, n, -INF};
    build(0);

    dp[0] = 0;
    update(0, 0, 0);
    vector<int> stk;

    map<ll, int> f;

    for(int i = 1; i <= n; i++) {
        int h = a[i], v = b[i];
        while(stk.size() > 0 && h < a[stk.back()]) {
            int idx = stk.back();
            del(f, val[idx]);
            stk.pop_back();
        }

        if(stk.size() == 0) {
            ll mx = query(0, 0, i - 1);
            val[i] = mx + v;
            f[val[i]]++;
        } else {
            int last = stk.back();
            ll mx = query(0, last, i - 1);
            val[i] = mx + v;
            f[val[i]]++;
        }
        auto it = f.end();
        it--;
        dp[i] = it -> first;

        update(0, i, dp[i]);
        stk.push_back(i);
        //cout << i << "  " << f << endl;
    }

    /*for(int i = 0; i <= n; i++) {
        cout << dp[i] << "  ";
    } cout << endl << endl;
    
    for(int i = 0; i <= n; i++) {
        cout << val[i] << "  ";
    } cout << endl << endl;*/
    
    cout << dp[n] << endl;
    
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
