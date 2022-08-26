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


const int N = 2e5 + 10;
ve<int> a[N];
ve<int> b[N];
int cnt[N];
int vals[N];

void solve() { 
  int l, r;
  cin >> l >> r;
  ll le = l, ri = r;
  ll res = (ri - le + 1) * (ri - le) * (ri - le - 1) / 6; //C(size, 3)
  
  for(int i = l; i <= r; i++) {
    a[i].clear();
    b[i].clear();
    int val = i;
    cnt[i] = 0;
    while(val % 2 == 0) val /= 2, cnt[i]++;
    vals[i] = 1;
    for(int j = 0; j <= cnt[i]; j++) {
        vals[i] *= 2;
    }
  }
  
  for(int i = l; i <= r; i++) {
    for(int j = i + i; j <= r; j += i) {
      a[j].pb(i);
    }
  }
  
  for(int i = 1; i <= r; i += 2) {
      for(int j = i + i; j <= r; j += i) {
          ll t = (vals[j] + 0ll) * i;
          if(t >= l && t < j ) {
              b[j].pb(i * vals[j]);
          }
      }
  }
  
  for(int i = l + 2; i <= r; i++) {
    ll sz = a[i].size();
    ll sum = (sz) * (sz - 1) / 2;
    

    int left = 0, right = b[i].size() - 1;
    while(left < right) {
        if(b[i][left] + b[i][right] > i) {
            sum += (right - left);
            right--;
        } else {
            left++;
        }
    }
    
    int k = 0;
    for(int j = 0; j < a[i].size() && k < b[i].size(); j++) {
      while(k < b[i].size() && b[i][k] <= a[i][j]) {
        k++;
      }
      int lo = k, hi = b[i].size() - 1;
      int pos = -1;
      while(lo <= hi) {
          int mid = lo + (hi - lo) / 2;
          if(b[i][mid] + a[i][j] > i) {
              pos = mid;
              hi = mid - 1;
          } else {
              lo = mid + 1;
          }
      }
      if(pos != -1) {
          sum += (b[i].size() - pos);
      }
    }
    

    k = 0;
    for(int j = 0; j < b[i].size() && k < a[i].size(); j++) {
      while(k < a[i].size() && a[i][k] <= b[i][j]) {
        k++;
      }
      
      int lo = k, hi = a[i].size() - 1;
      int pos = -1;
      while(lo <= hi) {
          int mid = lo + (hi - lo) / 2;
          if(a[i][mid] + b[i][j] > i) {
              pos = mid;
              hi = mid - 1;
          } else {
              lo = mid + 1;
          }
      }
      if(pos != -1) {
           sum += (a[i].size() - pos);
      }
      
    }
    res -= sum;
  }
  cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
  
  
