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

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>& nums, int r1, int r2) {
  if(r1 != r2) {
    nums[r1] = r2;
  }
}

const int N = 1010;
int a[N][N];

void output(int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  ve<int> nums(2 * n + 10);
  for(int i = 0; i < nums.size(); i++) {
    nums[i] = i;
  }

  //[0 : n - 1] : swap
  //[n : 2 * n - 1] : nonswap
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(i == j) continue;
      int id1 = i * n + j, id2 = j * n + i;
      if(id1 > id2) continue;
      int r1 = find(nums, i), r2 = find(nums, i + n);
      int r3 = find(nums, j), r4 = find(nums, j + n);
      if(a[i][j] > a[j][i]) {
        if(r1 == r3) {

        } else {
          swap(a[i][j], a[j][i]);
          merge(nums, r1, r4);
          merge(nums, r2, r3);
        }

      } else if(a[i][j] < a[j][i]) {
        //not swap
        if(r1 == r4 || r2 == r3) {
          swap(a[i][j], a[j][i]);
        } else {
          merge(nums, r1, r3);
          merge(nums, r2, r4);
        }
      }
    }
  }
  output(n);
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
