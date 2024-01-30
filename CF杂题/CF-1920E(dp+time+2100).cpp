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

//3:22
const int MOD = 998244353;
const int N = 2500 + 5;
ll dp[N][N];
//(n/1 + n/2 + n/3 ... n/n) => O(nlogn)
void solve() {
  int n, k;
  cin >> n >> k;
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= k; j++) {
      dp[i][j] = 0;
    }
  }
  
  for(int i = 0; i < k; i++) {
    dp[0][i] = 1;
  }

  for(int i = 1; i <= n; i++) {
    for(int last = 0; last < k; last++) {
      for(int cur = 0; cur + last < k && (cur + 1) * (last + 1) <= i; cur++) {
        dp[i][cur] += dp[i - ((cur + 1) * (last + 1))][last];
        dp[i][cur] %= MOD;
      }
    }
  }
  
  ll ans = 0;
  for(int i = 0; i < k; i++) {
    ans += dp[n][i];
    ans %= MOD;
  }

  printf("%lld\n", ans);
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
