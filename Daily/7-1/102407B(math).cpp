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


const int N = 1e5 + 10;
int a[N];
ull po[60], po1[60], C[60][60];
int n;
ll tot = 0;


void test() {
    vector<int> v(10);
    int sum = 0;
    for(int i = 1; i <= 999; i++) {
        int x = i;
        while(x > 0) {
            sum++;
            x /= 10;
        }
    }
    cout << sum << endl;
}

void init() {
    C[0][0] = 1;
    for(int i = 1;i < 60; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] );
      }
    }
}

ll ways(int n) {
  ll res = 0;
  for(int i = 1; i <= n; i++) {
    res += (C[n][i] * po1[n - i] * i);
  }
  return res;
}

ll cal(ll mid) {
  ull sum = 0;
  ull cur = 0;
  ull p = 1;
  int d = 1;
  while(sum < tot) {
    if(cur + p * (n - 1) <= mid) {
      sum += (p * d * (n - 1));
      cur += p * (n - 1);
    } else {
      ull more = mid - cur;
      sum += (more * d);
      break;
    }
    d++;
    p *= n;
  }
  return sum;
}

bool ok(ll x) {
  vector<int> base;
  vector<ll> b(n);
  ll y = x;
  while(y > 0) {
    base.push_back((int)(y % n));
    y /= n;
  }
  reverse(base.begin(), base.end());
  
  //cout << x << "  " << base << endl;
  
  for(int i = 1; i <= base.size() - 1; i++) {
    for(int j = 0; j < n; j++) {
        if(i == 1) {
            if(j != 0) b[j]++;
        } else {
            if(j == 0) {
              b[j] += ways(i - 1) * (n - 1);
            } else {
              b[j] += ways(i - 1) * (n - 1);
              b[j] += po[i - 1];
            }
            if(b[j] > a[j]) return false;
        }
    }
  }
  
  
  //same length
  for(int i = 0; i < base.size(); i++) {
    int d = base[i];
    if(d == 0) continue;
    int sz = base.size() - (i + 1);
    int mul = d;
    if(i == 0) mul--;
    for(int j = 0; j < n; j++) {
      b[j] += ways(sz) * (mul);
      if(b[j] > a[j]) return false;
    }

    for(int j = (i == 0 ? 1 : 0); j <= d - 1; j++) {
      b[j] += po[sz];
      if(b[j] > a[j]) return false;
    }
    
    for(int j = 0; j < i; j++) {
      int dd = base[j];
      b[dd] += po[sz] * (d);
      if(b[dd] > a[dd]) return false; 
    }
  }
  
  //all same
  for(int ba : base) {
      b[ba]++;
  }
  
  for(int i = 0; i < n; i++) {
    if(b[i] != a[i]) return false;
  }
  return true;
}

void solve() {
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    tot += a[i];
  }

  if(tot == 0) {
    cout << -1 << endl;
    return;
  }
  
  po[0] = 1;
  po1[0] = 1;
  for(int i = 1; i < 60; i++) {
      po[i] = po[i - 1] * n;
      po1[i] = po1[i - 1] * (n - 1);
  }

  ll l = 1, r = tot;
  ll res = -1;
  while(l <= r) {
    ll mid = l + (r - l) / 2;
    ll sum = cal(mid);
    if(sum == tot) {
      res = mid;
      break;
    }
    if(sum < tot) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
   
  if(res == -1) {
    cout << -1 << endl;
    return;
  }

  if(ok(res)) {
    cout << res << endl;
  } else {
    cout << -1 << endl;
  }

}


int main()
{
    init();
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}
