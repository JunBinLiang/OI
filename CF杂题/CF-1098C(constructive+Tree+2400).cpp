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

ll n, S;
const int N = 2e5 + 10;
int ans[N];
bool check(ll mid) {
  ll sum = 1;
  int id = 2;
  queue<pair<int, int>> q;
  q.push({1, 1});
  while(q.size() > 0 && id <= n) {
    pair<int, int> top = q.front(); q.pop();
    int lev = top.second;
    for(int i = 1; i <= mid && id <= n; i++) {
      sum += (1 + lev);
      q.push({id, lev + 1});
      id++;
    }
  }
  return sum <= S;
}

void build(int coe) {
  memset(ans, -1, sizeof(ans));
  queue<pair<int, int>> q;
  ll sum = S - 1;
  int id = 2;
  q.push({1, 1});
  while(q.size() > 0) {
    pair<int, int> top = q.front(); q.pop();
    int root = top.first, le = top.second;
    for(int i = 1; i <= coe && id <= n; i++) {
      ll remain = (n - id + 1);
      //take them as line
      ll x = (1 + remain) * remain / 2 + le * remain;
      if(x >= sum) {
        sum -= (1 + le);
        q.push({id, le + 1});
        ans[id] = root; 
        id++;
      } else {
        break;
      }
    }
  }

}

void solve() {
    cin >> n >> S;
    if((1 + n) * n / 2 < S || (n + n - 1) > S) {
      printf("NO \n");
      return;
    }

    int l = 1, r = n - 1;
    int res = -1;
    while(l <= r) {
      ll mid = l + (r - l) / 2;
      if(check(mid)) {
        res = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }

    build(res);
    printf("YES\n");
    for(int i = 2; i <= n; i++) {
      printf("%d ", ans[i]);
    }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
