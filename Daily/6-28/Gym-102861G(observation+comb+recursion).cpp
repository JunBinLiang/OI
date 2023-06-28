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
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 55;
ll C[N][N];
void init() {
  memset(C, 0, sizeof C);

  C[0][0] = 1;
  for(int i = 1;i <= 52; i++) {
    C[i][0]=1;
    for(int j = 1;j <= 52;j++) {
      C[i][j] = ( C[i-1][j] + C[i-1][j-1] );
    }
  }
}

ll atmost(vector<ll>& a, int i, int k, ll up) {
  if(k == 0) {
      return 1;
  }
  
  if(i >= a.size()) {
      return 0;
  }
  
  int n = a.size();
  if(a[i] > up) {
    return atmost(a, i + 1, k, up);
  } else {
    ll ways1 = C[n - (i + 1)][k];
    return ways1 + atmost(a, i + 1, k - 1, up - a[i]);
  }
}

void solve() {
  init();

  int n, k;
  ll l, r;
  cin >> n >> k;

  vector<ll> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  cin >> l >> r;
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());
  ll v1 = atmost(a, 0, k, r);
  ll v2 = atmost(a, 0, k, l - 1);
  ll res = v1 - v2;
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
