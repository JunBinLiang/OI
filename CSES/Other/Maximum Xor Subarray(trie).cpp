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
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
const int N = (2e5 + 100) * 32;
int tr[N][2];
int id = 0;
void add(int x) {
  int u = 0;
  for(int i = 30; i >= 0; i--) {
    if(x & (1 << i)) {
      if(tr[u][1] == -1) tr[u][1] = ++id;
      u = tr[u][1];
    } else {
      if(tr[u][0] == -1) tr[u][0] = ++id;
      u = tr[u][0];
    }
  }
}

int find(int x) {
  int u = 0;
  int res = 0;
  for(int i = 30; i >= 0; i--) {
    if(x & (1 << i)) {
      if(tr[u][0] != -1) {
        res |= (1 << i);
        u = tr[u][0];
      } else {
        u = tr[u][1];
      }
    } else {
      if(tr[u][1] != -1) {
        res |= (1 << i);
        u = tr[u][1];
      } else {
        u = tr[u][0];
      }
    }
  }
  return res;
}

void solve() {
  memset(tr, -1, sizeof tr);

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  int res = 0, xo = 0;
  for(int i = 0; i < n; i++) {
    xo ^= a[i];
    res = max(res, xo);
    if(i > 0) {
        res = max(res, find(xo));
    }
    add(xo);
  }
  
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
