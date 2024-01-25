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

const int N = 1e5 + 10, M = 305;
int a[N];
ll s1[M][N], s2[M][N];

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);

  int sq = sqrt(n);
  sq = min(sq, 300);
  for(int j = 1; j <= sq; j++) {
    for(int i = 0; i < n; i++) {
      int k = i / j + 1;
      s1[j][i] = (a[i] + 0ll) * k;
      s2[j][i] = a[i];
      if(i - j >= 0) s1[j][i] += s1[j][i - j], s2[j][i] += s2[j][i - j];
    }
  }
  
  vector<ll> ans(m); 
  for(int i = 0; i < m; i++) {
    int s, d, k;
    scanf("%d%d%d", &s, &d, &k);
    s--;
    if(d > sq) {
      for(int j = 1; j <= k; j++) {
        ans[i] += ((a[s] + 0ll) * j);
        s += d;
      }
    } else {
      ans[i] = (s1[d][s + d * (k - 1)]);
      ll sum = s2[d][s + d * (k - 1)];
      if(s - d >= 0) ans[i] -= s1[d][s - d], sum -= s2[d][s - d];
      int l = s / d;
      ans[i] -= ((l + 0ll) * sum);
    }
  }

  for(auto& x : ans) printf("%lld ", x);
  printf("\n");
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
