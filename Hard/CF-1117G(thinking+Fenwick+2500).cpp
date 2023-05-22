
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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

namespace Fenwick {
  const int SIZE = 1e6 + 100;
  ll tree[2][SIZE];
  void init() {
    FOR(i, 0, SIZE) {
      tree[0][i] = 0;
      tree[1][i] = 0;
    }
  }

  void update(int which, int i, ll val) {
    i++;
    while(i < SIZE){
      tree[which][i] += val;
      i += (i & -i);
    }
  }

  ll pre(int which, int i) {
    ll sum = 0;
    while(i > 0){
      sum += tree[which][i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int which, int i, int j) {
      return pre(which, j + 1) - pre(which, i);
  }
}

const int N = 1e6 + 10;
int n, m;
int a[N];
int l[N], r[N];
ll ans[N];
pair<int, int> q[N];
vector<pair<int, int>> q1[N], q2[N];

void solve() {
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        scanf("%d", &a[i]);
    }

    memset(ans, 0, sizeof ans);
    memset(l, 0, sizeof l);
    FOR(i, 0, N) {
        r[i] = n + 1;
    }

    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        while(stk.size() > 0 && a[i] > a[stk.back()]) {
            int idx = stk.back();
            r[idx] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }

    for(int i = n; i >= 1; i--) {
        while(stk.size() > 0 && a[i] > a[stk.back()]) {
            int idx = stk.back();
            l[idx] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }

    //offline query
    FOR(i, 0, m) {
        scanf("%d", &q[i].first);
    }
    FOR(i, 0, m) {
        scanf("%d", &q[i].second);
    }
    FOR(i, 0, m) {
        int le = q[i].first, ri = q[i].second;
        q1[ri].pb({le, i});
        q2[le].pb({ri, i});
    }
    
    /*FOR(i, 1, n + 1) cout << r[i] << " ";
    cout << endl;
    FOR(i, 1, n + 1) cout << l[i] << " ";
    cout << endl << endl;*/

    set<pair<int, int>> s;
    Fenwick :: init();
    for(int i = 1; i <= n; i++) {
        while(s.size() > 0) {
            auto it = s.begin();
            int idx = it -> second;
            if(r[idx] <= i) {
                ll old = Fenwick :: query(1, idx, idx);
                Fenwick :: update(1, idx, -old);
                Fenwick :: update(1, idx, r[idx] - idx);
                Fenwick :: update(0, idx, -1);
                s.erase(*it);
               // cout << "yes " << idx << " " << old << " " << r[idx] - idx << endl;
            } else {
                break;
            }
        }
        
        s.insert({r[i], i});
        Fenwick :: update(0, i, 1); //cnt
        Fenwick :: update(1, i, n - i + 1);

        for(pair<int, int>&p : q1[i]) {
            int le = p.first, idx = p.second;
            ll tot = Fenwick :: query(1, le, i);
            
            ll cnt = Fenwick :: query(0, le, i);
            tot -= (cnt * (n - i));
            ans[idx] += tot;
            //cout << le << " " << i << " " << "   |" << cnt << " " << tot << endl;
        }
    }
    
    s.clear();
    Fenwick :: init();
    for(int i = n; i >= 1; i--) {
        while(s.size() > 0) {
            auto it = s.begin();
            int idx = it -> second;
            if(l[idx] >= i) {
                ll old = Fenwick :: query(1, idx, idx);
                Fenwick :: update(1, idx, -old);
                Fenwick :: update(1, idx, idx - l[idx]);
                Fenwick :: update(0, idx, -1);
                s.erase(*it);
                //cout << "yes " << i << "  " << idx << " " << old << " " << idx - l[idx] << endl;
            } else {
                break;
            }
        }
        
        s.insert({-l[i], i});
        Fenwick :: update(0, i, 1); //cnt
        Fenwick :: update(1, i, i);

        for(pair<int, int>&p : q2[i]) {
            int ri = p.first, idx = p.second;
            ll tot = Fenwick :: query(1, i, ri);
            ll cnt = Fenwick :: query(0, i, ri);
            tot -= (cnt * (i - 1));
            ans[idx] += tot;
        }
    }
   

    for(int i = 0; i < m; i++) {
        int le = q[i].first, ri = q[i].second;
        cout << ans[i] - (ri - le + 1) << " ";
    }
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
