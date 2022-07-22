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


bool COMP(pair<int, int>&p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}

int Next(int val, int k) {
  int x = val / k;
  int y = val / x;
  return y + 1;
}

const int N = 1e5 + 5;
queue<pair<int, int>> q[N];
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  int res = 1e9, mn = 1e9;
  for(int i = 0; i < N; i++) {
    while(q[i].size() > 0) q[i].pop();
  }

  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    q[x].push({x, 1});
    mn = min(mn, x);
  }
  

  for(int i = 100000; i >= 0; i--) {
    if(q[i].size() == 0) continue;
    res = min(res, i - mn);
    while(q[i].size() > 0) {
      pair<int, int> p = q[i].front(); q[i].pop();
      int x = p.first, y = p.second;
      int nxt = Next(x, y);
      if(nxt <= k) {
        if(nxt > x) {
          printf("%d \n", res);  
          return;
        }

        q[x / nxt].push({x, nxt});
        mn = min(mn, x / nxt);
      } else {
        printf("%d \n", res);  
        return;
      }
    }
    queue<pair<int, int>> qq;
    swap(qq, q[i]);
  }

  printf("%d \n", res);  
}

int main() {
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
}
