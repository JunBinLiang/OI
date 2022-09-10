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
  const int SIZE = 200000 + 100;
  int tree[SIZE];
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

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}


const int N = 1e5 + 10;
int n;
ll res = 0;
ll a[N];
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
      scanf("%lld", &a[i]);
      a[i] += a[i - 1];
    }

    vector<ll> b;
    for(int i = 1; i <= n; i++) {
      if(a[i] > a[n] || a[i] < 0) {
        cout << -1 << endl;
        return 0;
      }
      b.pb(a[i]);
    }
    sort(b.begin(), b.end());
    int id = 1;
    map<ll, int> f;
    for(int i = 0; i < b.size(); i++) {
      int j = i;
      while(j < b.size() && b[i] == b[j]) j++;
      f[b[i]] = id++;
      i = j - 1;
    }

    Fenwick :: init(); 
    for(int i = 1; i <= n; i++) {
      res += Fenwick :: query(f[a[i]] + 1, id + 1);
      Fenwick :: update(f[a[i]], 1);
    }
    cout << res << endl;
    return 0;
}   
