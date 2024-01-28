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
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 2e5 + 10, MOD = 1e9 + 7;
int a[N];

namespace Fenwick {
  const int SIZE = 200000 + 100;
  ll tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n; i++) tree[i] = 0;
  }
  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      tree[i] %= MOD;
      i += (i & -i);
    }
  }
  ll pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      sum %= MOD;
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return (pre(j + 1) - pre(i) + MOD) % MOD;
  }
}

namespace Fenwick1 {
  const int SIZE = 200000 + 100;
  ll tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n; i++) tree[i] = 0;
  }
  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      tree[i] %= MOD;
      i += (i & -i);
    }
  }
  ll pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      sum %= MOD;
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return (pre(j + 1) - pre(i) + MOD) % MOD;
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> b(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    b[i] = {a[i], -i};
  }

  //pre-processing
  sort(b.begin(), b.end());
  unordered_map<int, int> f;
  for(int i = 0; i < b.size(); i++) {
    a[-b[i].second] = i + 1;
  }

  //init right max
  vector<int> maxR(n);
  for(int i = n - 1; i >= 0; i--) {
    maxR[i] = a[i];
    if(i + 1 < n) maxR[i] = max(maxR[i], maxR[i + 1]);
  }
  
  
  /*for(int i = 0; i < n; i++) {
      cout << a[i] << " ";
  } cout << endl;*/


  vector<ll> L(n), R(n);
  Fenwick :: init(n + 5);
  for(int i = 0; i < n; i++) {
    ll sum = Fenwick :: query(0, a[i] - 1) + 1;
    Fenwick :: update(a[i], sum);
    L[i] = sum;
  }
  
  //cout << L << endl;

  Fenwick :: init(n + 5);
  Fenwick1 :: init(n + 5);
  for(int i = n - 2; i >= 0; i--) {
    int l = i + 1, r = n - 1, p = -1;
    while(l <= r) {
      int mid = l + (r - l) / 2;
      if(maxR[mid] > a[i]) {
        p = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    //cout << i << " " << p << endl;
    if(p == -1) {
      Fenwick :: update(a[i], 1);
      Fenwick1 :: update(a[i], 0);
    } else {
      int v = a[p];
      ll sum = 0;
      if(a[i] + 1 <= v - 1) {
        sum += Fenwick1 :: query(a[i] + 1, v - 1);
      }
      sum += Fenwick :: query(v + 1, n + 1);
      sum %= MOD;
      Fenwick :: update(a[i], 1 + Fenwick :: query(a[i] + 1, n + 1));
      Fenwick1 :: update(a[i], sum + 1);
    }
  }

  for(int i = 0; i < n - 1; i++) {
    R[i] = Fenwick1 :: query(a[i], a[i]);
  }
  
  /*cout << endl;
  for(int i = 0; i < n; i++) {
      cout << Fenwick :: query(a[i], a[i]) << " ";
  } cout << endl;
  cout << R << endl;*/
  
  ll res = 0;
  for(int i = 0; i < n - 1; i++) {
    res += (L[i] * R[i]);
    res %= MOD;
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

/*
4
4 4 4 5
*/
