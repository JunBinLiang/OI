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




void solve() {
  ll n, m, k;
  cin >> n >> m >> k;
  ll t = (n + 0ll) * m - k + 1;

  ll res = -1;
  ll l = 1, r = 9999999999ll;
  
  while(l <= r) {
    ll mid = l + (r - l) / 2;

    ll sum = 0;
    ll leftBound = mid + 1;
    
    for(ll i = 1; i <= n; i++) {
        if((m + 0ll) * i <= mid) {
            sum += m;
        } else {
            leftBound = i;
            break;
        }
    }
    
    while(leftBound <= mid) {
      ll nxt = mid / (mid / leftBound);
      if(nxt >= min(mid, n)) {
        sum += ((min(mid, n) + 0ll) - leftBound + 1) * (mid / leftBound);
        break;
      } else {
        sum += (nxt - leftBound + 1) * (mid / leftBound);
      }
      leftBound = nxt + 1;
    }
    
    if(t <= sum) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }


  if(res == -1) {
    cout << "Oops" << endl;
    return;
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
