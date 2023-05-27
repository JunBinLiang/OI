
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
#include <list>

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int MAX = 800000 + 100;

struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
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



const int N = 2e5 + 10;
ll v1[N], v2[N];
pair<int, int> e1[N], e2[N];
int cost[N];
int n, m;
bool comp(vector<int>& a, vector<int>& b) {
    return a[0] < b[0];
}
bool comp1(vector<int>& a, vector<int>& b) {
    return a[1] < b[1];
}

void solve() {
    memset(v1, -1, sizeof v2);
    memset(v1, -1, sizeof v2);
    cin >> n >> m;
    vector<vector<int>> a, b;
    vector<int> c;
    for(int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        e1[i] = {l, r};
        a.push_back({l, r, i});
        c.push_back(l); 
        c.push_back(r);
    }
    for(int i = 0; i < m; i++) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        e2[i] = {l, r};
        cost[i] = w;
        b.push_back({l, r, w, i});
        c.push_back(l); c.push_back(r);
    }
    
    sort(c.begin(), c.end());
    int id = 0;
    map<int, int> f;
    for(int i = 0; i < c.size(); i++) {
        int j = i;
        while(j < c.size() && c[i] == c[j]) j++;
        f[c[i]] = id++;
        i = j - 1;
    }
    tree[0] = {0, id + 1, 0};
    build(0);
    
    //first part
    sort(a.begin(), a.end(), comp);
    sort(b.begin(), b.end(), comp);
    int j = 0;
    set<pair<int, int>> s1;
    for(int i = 0; i < b.size(); i++) {
        int L = b[i][0], R = b[i][1], idx1 = b[i][3];
        ll w = b[i][2];
        while(j < a.size() && a[j][0] <= L) {
            s1.insert({a[j][1], a[j][2]});
            j++;
        }

        if(s1.size()) {
            auto it = s1.end();
            it--;
            if(it -> first >= L) {
                int r = it -> first;
                if((min(r, R) - L) * w > v1[idx1]) {
                    v1[idx1] = (min(r, R) - L) * w;
                }
            }
        }
    }
    
    //second part, total overlap
    j = 0;
    for(int i = 0; i < a.size(); i++) {
        int L = a[i][0], R = a[i][1], idx = a[i][2];
        while(j < b.size() && b[j][0] <= L) {
            int r = b[j][1];
            update(0, f[r], b[j][2]);
            j++;
        }

        int mx = query(0, f[R], id);
        ll sz = (R - L);
        if(sz * mx > v2[idx]) {
            v2[idx] = sz * mx;
        }
    }

    
    //third part
    sort(a.begin(), a.end(), comp1);
    sort(b.begin(), b.end(), comp1);
    j = a.size() - 1;
    s1.clear();
    for(int i = m - 1; i >= 0; i--) {
        int L = b[i][0], R = b[i][1], idx1 = b[i][3];
        ll w = b[i][2];
        while(j >= 0 && a[j][1] >= R) {
            s1.insert({a[j][0], a[j][2]});
            j--;
        }

        if(s1.size()) {
            auto it = s1.begin();
            if(it -> first <= R) {
                int l = it -> first;
                if((R - max(L, l)) * w > v1[idx1]) {
                    v1[idx1] = (R - max(L, l)) * w;
                }
            }
        }
    }


    int res1 = -1, res2 = -1;
    ll mx = 0;
    for(int i = 0; i < m; i++) {
        if(v1[i] > mx) {
            res2 = i;
            mx = v1[i];
        }
    }
    

    for(int i = 0; i < n; i++) {
        int l = e1[i].first, r = e1[i].second;
        int L = e2[res2].first, R = e2[res2].second;
        if(r < L || L > r) continue;
        ll o = min(r, R) - max(l, L);
        if(o * cost[res2] == mx) {
            res1 = i;
        }
    }

    bool find = false;
    for(int i = 0; i < n; i++) {
        if(v2[i] > mx) {
            mx = v2[i];
            res1 = i;
            find = true;
        }
    }
    
    if(find) {
        for(int i = 0; i < m; i++) {
            int l = e2[i].first, r = e2[i].second;
            int L = e1[res1].first, R = e1[res1].second;
            if(r < L || L > r) continue;
            ll o = min(r, R) - max(l, L);
            if(o * cost[i] == mx) {
                res2 = i;
            }
        }
    }


    if(mx == 0) {
        cout << 0 << endl;
        return;
    }
    cout << mx << endl;
    cout << res1 + 1 << " " << res2 + 1 << endl;

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
