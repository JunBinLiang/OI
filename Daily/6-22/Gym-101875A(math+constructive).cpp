
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

ll LCM(ll x, ll y) {
  ll g = __gcd(x, y);
  return x * y / g;
}

void solve() {
  int n, k;
  cin >> n >> k;
  if(k == 1) {
    cout << (n - 1) << endl;
    return;
  }

  if(__gcd(n, k) == 1) {
    cout << (n - 1ll) * k << endl;
    return;
  }
  //1 5 9 13
  //1 5 3 5
  ll lcm = LCM(n, k);
  ll cnt = lcm / k;
  ll score = (cnt - 1) * k + (k - 1);
  ll edge = n - 1;
  ll res = (edge / cnt) * score + (edge % cnt) * k;
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
