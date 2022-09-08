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
int a[N];
ll INF = 10000000000000000ll;
ll dp[N][2][4][2];
int n;
ll dfs(int i, int pre, int neg, int state) {
  if(i >= n) {
    if(state == 1 && (n + neg) % 3 == 1) {
      return 0;
    } else {
      return -INF;
    }
  }
  if(dp[i][pre][neg][state] != -INF) {
    return dp[i][pre][neg][state];
  }

  ll res = -INF;
  if(state == 0) {
    if(pre == 0) {
      res = max(res, a[i] + dfs(i + 1, 0, neg, 1));
      res = max(res, -a[i] + dfs(i + 1, 1, (neg + 1) % 3, state));
    } else {
      res = max(res, a[i] + dfs(i + 1, 0, neg, state));
      res = max(res, -a[i] + dfs(i + 1, 1, (neg + 1) % 3, 1));
    } 
  } else {
    res = max(res, a[i] + dfs(i + 1, 0, neg, state));
    res = max(res, -a[i] + dfs(i + 1, 1, (neg + 1) % 3, state));
  }
  return dp[i][pre][neg][state] = res;
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    if(n == 1) {
        cout << a[0] << endl;
        return 0;
    }

    for(int i = 0; i <= n; i++) {
      for(int j = 0; j < 2; j++) {
        for(int k = 0; k < 4; k++) {
          for(int l = 0; l < 2; l++) {
            dp[i][j][k][l] = -INF;
          }
        }
      }
    }
    ll res = max(a[0] + dfs(1, 0, 0, 0), -a[0] + dfs(1, 1, 1, 0));
    cout << res << endl;
    return 0;
}
