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


const int N = 1e6 + 5;
int a[N * 2];
int f[N * 2];

void add(int x, int i) {
  if(i > 20) {
      f[x]++;
      return;
  }
  
  if(f[x] > 1) {
    return;
  }
  add(x, i + 1);
  if(x & (1 << i)) {
    add(x ^ (1 << i), i + 1);
  }
}

void solve() { 
  int n;
  int res = 0;
  scanf("%d", &n);
  memset(f, 0, sizeof(f));
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = n - 1; i >= 0; i--) {
    if(i + 2 < n) {
      int now = 0;
      for(int j = 20; j >= 0; j--) {
        if(!(a[i] & (1 << j)) && f[now | (1 << j)] > 1) {
          now |= (1 << j);
        }
      }
      res = max(res, a[i] | now);
    }
    add(a[i], 0); 
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
  
  
