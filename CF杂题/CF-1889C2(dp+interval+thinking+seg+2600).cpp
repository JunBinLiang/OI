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
using ull = unsigned long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mx;
} tree[11][MAX * 4];

void build(int ith, int id) {
  int l = tree[ith][id].l, r = tree[ith][id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[ith][id * 2 + 1] = {l, mid, -1};
  tree[ith][id * 2 + 2] = {mid + 1, r, -1};
  build(ith, id * 2 + 1);
  build(ith, id * 2 + 2);
}

void update(int ith, int id, int index, int val) { 
  int l = tree[ith][id].l, r = tree[ith][id].r;
  if(l == r) {
    tree[ith][id].mx = max(tree[ith][id].mx, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(ith, left, index, val);
  } else {
    update(ith, right, index, val);
  }
  tree[ith][id].mx = max(tree[ith][left].mx, tree[ith][right].mx);
}

int query(int ith, int id, int s, int e) {
  int l = tree[ith][id].l, r = tree[ith][id].r;
  if(l == s && r == e){
    return tree[ith][id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(ith, left, s, e);
  } else if(s >= mid + 1) {
      return query(ith, right, s, e);
  } else {
    return max(query(ith, left, s, mid), query(ith, right, mid + 1, e));
  }
}


const int N = 2e5 + 10;
int dp[N][11];
void solve() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = -1;
        }
    }
    
    for(int i = 0; i <= k; i++) {
        tree[i][0] = {0, n, -1};
        build(i, 0);
    }


    vector<pair<int, int>> a;
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        a.push_back({l, r});
    }

    sort(a.begin(), a.end());
    //for(auto p : a) cout << p.first << " " << p.second << endl;


    dp[0][0] = 0;
    update(0, 0, 0, 0);

    int x = 0;
    set<pair<int, int>> lefts, rights;
    for(int i = 1; i <= n; i++) {
        while(x < a.size() && a[x].first <= i) {
            int l = a[x].first, r = a[x].second;
            lefts.insert({l, x});
            rights.insert({r, x});
            x++;
        }

        while(rights.size() > 0) {
            auto it = rights.begin();
            if(it -> first < i) {
                int idx = it -> second;
                if(lefts.find({a[idx].first, idx}) != lefts.end()) {
                    lefts.erase({a[idx].first, idx});
                }
                rights.erase(*it);
            } else {
                break;
            }
        }

        vector<pair<int, int>> b;
        if(lefts.size() > 0) {
            auto it = lefts.end();
            it--;
            while(b.size() <= k) {
                b.push_back(*it);
                if(it == lefts.begin()) break;
                it--;
            }
        }
        reverse(b.begin(), b.end());
        
        
        for(int j = 0; j <= k; j++) {
            int count = 0;
            int cur = i;
            for(int o = b.size() - 1; o >= 0; o--) {
                if(j < count) break;
                if(b[o].first <= cur - 1) {
                    int mxv = query(j - count, 0, b[o].first, cur - 1);
                    if(mxv != -1) {
                        dp[i][j] = max(dp[i][j], 1 + mxv);
                        update(j, 0, i, dp[i][j]);
                            
                    }
                }
                
                count++;
                cur = b[o].first;
            }
            
            
            if(b.size() == 0) {
                cur = i - 1;
            } else {
                cur = b[0].first - 1;
            }
            
            if(j >= b.size()) {
                int mxv = query(j - b.size(), 0, 0, cur);
                if(mxv != -1) {
                    dp[i][j] = max(dp[i][j], 1 + mxv);
                    update(j, 0, i, dp[i][j]);
                }
            }
        }
    }

    int res = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            res = max(res, dp[i][j]);
        }
    }
    cout << res << endl;
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
