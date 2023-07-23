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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 
const int N = 1e6 + 10;
ll cnt[N], dp[N];
void solve() {
    memset(cnt, 0, sizeof cnt);
    memset(dp, 0, sizeof dp);

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        cnt[x]++;
    }


    for(int i = N - 1; i >= 1; i--) {
        ll s = cnt[i];
        for(int j = i + i; j < N; j += i) {
            s += cnt[j];
            dp[i] -= dp[j];
        }
        ll p = (s - 1ll) * s / 2;
        dp[i] += p;
    }
    //for(int i = 1; i <= 20; i++) cout << dp[i] << " ";
    //cout << endl;
    cout << dp[1] << endl;
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

