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

int mod = 998244353;
const double PI = acos(-1);
bool is[20];
int n, m;
const int md = 998244353;
const int gen = 3;
inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}
 
int pw(int a, int b) {
  int x = 1, step = 1 << 30;
  while (step > 0) {
    x = (long long)x * x % md;
    if (step & b) x = (long long)x * a % md;
    step >>= 1;
  }
  return x;
}
 
void fft(vector <int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int j = 0;
    int x = i, y = n - 1;
    while (y > 0) {
      j = (j << 1) + (x & 1);
      x >>= 1;
      y >>= 1;
    }
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1; len < n; len *= 2) {
    int root = pw(gen, (md - 1) / (2 * len));
    for (int i = 0; i < n; i += 2 * len) {
      int w = 1;
      for (int j = 0; j < len; j++) {
        int u = a[i + j];
        int v = (long long)a[i + j + len] * w % md;
        a[i + j] = u + v;
        if (a[i + j] >= md) a[i + j] -= md;
        a[i + j + len] = u - v;
        if (a[i + j + len] < 0) a[i + j + len] += md;
        w = (long long)w * root % md;
      }
    }
  }
}
 
vector<int> multiply(vector<int> a, vector<int> b, int k) {
  int nn = 4;
  while (nn <= a.size() + b.size()) nn <<= 1;
  //cout <<a.size() << " " << b.size() <<" " << nn << endl;
  a.resize(nn);
  b.resize(nn);
  fft(a);
  fft(b);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * b[i] % md;
  reverse(++a.begin(), a.end());
  fft(a);
  int inv = pw(nn, md - 2);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * inv % md;
  int sz = a.size();
  a.resize(min(sz, k * 9 + 1));
  return a;
}

ve<int> divide(int k) {
  if(k == 1) {
    ve<int> nums(10);
    for(int i = 0; i < nums.size(); i++) {
      if(is[i]) nums[i] = 1;
    }
    return nums;
  }
  int x = k / 2;
  int y = k - x;
  ve<int> nums1 = divide(x);
  if(x == y) {
      ve<int> nums2(nums1.begin(), nums1.end());
      return multiply(nums1, nums2, k);
  } else {
    ve<int> nums2 = divide(y);
    return multiply(nums1, nums2, k);
  }
}


void solve() {
  cin >> n >> m;
  memset(is, 0, sizeof is);
  for(int i = 0; i < m; i++) {
    int x; cin >> x;
    is[x] = true;
  }

  ll res = 0;
  ve<int> c = divide(n / 2);
  for(int i = 0; i < c.size(); i++) {
    ll x = c[i], y = c[i];
    ll sum = (x * y) % mod;
    res += sum;
    res %= mod;
  }
  cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}

