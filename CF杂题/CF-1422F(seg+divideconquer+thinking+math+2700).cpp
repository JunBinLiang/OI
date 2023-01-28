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

const int N = 2e5 + 10, mod = 1e9 + 7;
bool is[610];
int ids[610];
vector<int> p;
int last[N], pos[N];

vector<int> c[100][19];
int vals[100][19];

int n, m;
int a[N];
ll res = 0;


void init() {
    memset(is, false, sizeof is);
    for(int i = 2; i < 600; i++) {
        if(is[i]) continue;
        p.push_back(i);
        for(int j = i; j < 600; j += i) {
            is[j] = true;
        }
    }
    for(int i = 0; i < p.size(); i++) {
        ids[p[i]] = i;
    }

}


void add(int idx, int val, int t, int cnt) {
    if(val == 1) return;
    c[ids[val]][cnt].push_back(idx);
    vals[ids[val]][cnt] = t;
}

int find(int ith, int k, int l, int r) {
    int left = 0, right = c[ith][k].size() - 1;
    int pos = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(c[ith][k][mid] >= l) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    if(pos != -1) {
        if(c[ith][k][pos] <= r) {
            return vals[ith][k];
        }
    }
    return -1;
}


///////////////////////////////////////////////////////////////////////
//query >= 500
const int MAX = 1e5 + 10;
struct Node {
  int l, r;
  vector<pair<int, int>> a;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  vector<pair<int, int>>& vec = tree[id].a;
  for(int i = l; i <= r; i++) {
      int v = a[i];
      if(v == -1) {
          vec.push_back({-1, 1});
      } else {
          vec.push_back({last[i], v});
      }
  }
  sort(vec.begin(), vec.end());
  for(int i = 1; i < vec.size(); i++) {
      vec[i].second = ((vec[i].second + 0ll) * vec[i - 1].second) % mod;
  }
  
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid};
  tree[id * 2 + 2] = {mid + 1, r};
  build(id * 2 + 1);
  build(id * 2 + 2);
}


ll bin(vector<pair<int, int>>& vec, int left) {
    int l = 0, r = vec.size() - 1;
    int res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(vec[mid].first < left) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if(res == -1) return 1;
    return vec[res].second;
}

int query(int id, int s, int e, int leftBound) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    vector<pair<int, int>>& vec = tree[id].a;
    int ret = bin(vec, leftBound);
    return ret;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e, leftBound);
  } else if(s >= mid + 1) {
      return query(right, s, e, leftBound);
  } else {
    int v1 = query(left, s, mid, leftBound), v2 = query(right, mid + 1, e, leftBound);
    int res = ((v1 + 0ll) * v2 % mod);
    return res;
  }
}
/////////////////////////////////////////////////////////////////////////////


void solve() {
    init();
    memset(a, -1, sizeof a);
    memset(last, -1, sizeof last);
    memset(pos, -1, sizeof pos);
    scanf("%d", &n);

    
    for(int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        for(int& j : p) {
            if(j > val) break;
            if(val % j == 0) {
                int cnt = 0;
                int old = val;
                while(val % j == 0) val /= j, cnt++;
                if(j <= 459) {
                    add(i, j, old / val, cnt);
                } else {
                    a[i] = j;
                    last[i] = pos[j];
                    pos[j] = i;
                }
            }
        }
        if(val > 1) {
            if(val <= 459) {
                add(i, val, val, 1);
            } else {
                a[i] = val;
                last[i] = pos[val];
                pos[val] = i;
            }
        }
    }
    
    tree[0] = {0, n - 1};
    build(0);
    
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int ans = (int)(res);
        l = (ans + l) % n + 1;
        r = (ans + r) % n + 1;
        l--;
        r--;
        if(l > r) swap(l, r);
        
        res = 1;
        for(int j = 0; j < 89; j++) {
            for(int k = 18; k >= 0; k--) {
                int v = find(j, k, l, r);
                if(v != -1) {
                    res *= v;
                    res %= mod;
                    break;
                }
            }
        }
        
        ll v =  query(0, l, r, l);
        if(v != 0) res *= v;
        res %= mod;
        printf("%lld\n", res);
    }
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
