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


namespace Fenwick {
  const int SIZE = 2e5 + 100;
  ll tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}


const int N = 2e5 + 10;
ve<int> a[N];
ll ans[N];
vector<pair<int, int>> q[N];
void solve() { 
  for(int i = 1; i < N; i++) {
    for(int j = i + i; j < N; j += i) {
      a[j].pb(i);
    }
  }

  Fenwick :: init();

  int t; 
  cin >> t;
  for(int i = 0; i < t; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    ll x = r - l + 1;
    ans[i] = (x) * (x - 1) * (x - 2) / 6;
    q[r].pb({l, i});
  }

  for(int i = 1; i < N; i++) {
    for(int j = 0; j < a[i].size(); j++) {
      Fenwick :: update(a[i][j], a[i].size() - j - 1);
    }

    //LCM(i, j, k) = 2 * k
    //i + j > k
    //k/2 < j < k
    //must in form
    //(2k/5, 2k/3, k), (k/2, 2k/3, k)
    if(i % 6 == 0) {
      Fenwick :: update(i / 2, 1);
    }
    if(i % 15 == 0) {
      Fenwick :: update(2 * i / 5, 1);
    }

    for(pair<int, int>& p : q[i]) {
      int l = p.first, idx = p.second;
      ans[idx] -= (Fenwick :: query(l, i));
    }
  }


  for(int i = 0; i < t; i++) {
    printf("%lld\n", ans[i]);
  }

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
