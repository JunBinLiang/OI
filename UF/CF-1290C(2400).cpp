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


int n, k;
const int N = 3e5 + 10;
ve<int> g[N];

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>& nums, ve<int>& cost, int r1, int r2) {
  if(r1 != r2) {
    nums[r1] = r2;
    cost[r2] += cost[r1];
  }
}

int get(ve<int>&nums, ve<int>& cost, int x) {
  return min(cost[find(nums, x)], cost[find(nums, x + k)]);
}

void solve() {
  scanf("%d%d", &n, &k);
  string s;
  cin >> s;

  for(int i = 0; i < k; i++) {
    int m; scanf("%d", &m);
    ve<int> a(m);
    for(int j =  0; j < m; j++) {
      scanf("%d", &a[j]);
      a[j]--;
      g[a[j]].pb(i);
    }
  }  

  //0 - k - 1 : take
  //k - 2 * k - 1 : not take
  ve<int> nums(2 * k + 1);
  ve<int> cost(2 * k + 1);
  for(int i = 0; i < nums.size(); i++) nums[i] = i;
  for(int i = 0; i < k; i++) cost[i] = 1;
  cost[2 * k] = 1e9;
  int big = 2 * k;

  ll ans = 0;
  for(int i = 0; i < n; i++) {
    if(g[i].size() == 1) {
      int x = g[i][0];
      if(s[i] == '0') { //take
        ans -= get(nums, cost, x);
        int r1 = find(nums, x + k);
        int r2 = find(nums, big);
        merge(nums, cost, r1, r2);
      } else { //not take
        ans -= get(nums, cost, x);
        int r1 = find(nums, x);
        int r2 = find(nums, big);
        merge(nums, cost, r1, r2);
      }
      ans += get(nums, cost, x);
      //cout << i << " " <<x << " " <<find(nums,x) << "  " << find(nums, x + k) << " " << get(nums, cost, x) << endl;
      //if(i == 1) cout << cost[2] << " " << cost[5] << endl;

    } else if(g[i].size() == 2) {
      int x = g[i][0], y = g[i][1];
      if(s[i] == '0') {
        if(find(nums, x) != find(nums, y + k)) { //take only one
          ans -= (get(nums, cost, x) + get(nums, cost, y));
          int r1 = find(nums, x), r2 = find(nums, y + k);
          int rr1 = find(nums, y), rr2 = find(nums, x + k);
          merge(nums, cost, r1, r2);
          merge(nums,cost, rr1, rr2);
          ans += get(nums, cost, x);
        }
      } else {
        if(find(nums, x) != find(nums, y)) {
          ans -= (get(nums, cost, x) + get(nums, cost, y));
          int r1 = find(nums, x), r2 = find(nums, y);
          int rr1 = find(nums, y + k), rr2 = find(nums, x + k);
          merge(nums, cost, r1, r2);
          merge(nums,cost, rr1, rr2);
          ans += get(nums, cost, x);
        }
      }
    }
    printf("%d \n", ans);
  }

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
