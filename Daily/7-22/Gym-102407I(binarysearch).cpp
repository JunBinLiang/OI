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
 
void solve() {
    ll n, x, y, d;
    cin >> n >> y >> x >> d;
    ll res = 0;

    ll up = n - y, down = y - 1;
    
    if(x > 1) {
        ll l = max(1ll, x - d), r = x - 1;
        ll L = l, R = r;
        ll p = 0;
        ll shift = d - (x - l);
        while(l <= r) {
            ll mid = l + (r - l) / 2;
            ll cnt = mid - L + shift;
            if(cnt <= up) { 
                p = (mid - L + 1);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        res += p;
        //cout << "p " << p << endl;

        l = max(1ll, x - d); r = x - 1;
        p = 0;
        while(l <= r) {
            ll mid = l + (r - l) / 2;
            ll cnt = mid - L + shift;
            if(cnt <= down) {
                p = (mid - L + 1);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        res += p;
       // cout << "p " << p << endl;
    }
    
    if(x + 1 <= n) {
        ll l = x + 1, r = min(n, x + d);
        ll L = l, R = r;
        ll p = 0;
        ll shift = d - (r - x);
        while(l <= r) {
            ll mid = l + (r - l) / 2;
            ll cnt = R - mid + shift;
            if(cnt <= up) {
                p = (R - mid + 1);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        res += p;

        l = x + 1; r = min(n, x + d);
        p = 0;
        while(l <= r) {
            ll mid = l + (r - l) / 2;
            ll cnt = R - mid + shift;
            if(cnt <= down) {
                p = (R - mid + 1);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        res += p;
    }
    

    if(y + d <= n) res++;
    if(y - d >= 1) res++;
    //duplicate count
    if(x - d >= 1) {
        res--;
    }
    if(x + d <= n) {
        res--;
    }
    cout << res << endl;
} 

/*
1000000000000000000 123456789987654321 987654321123456789 543211234567899876
679013703432097408
*/
    

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

