  


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

//3 : 05
const int N = 200000 + 100;
int a[N], b[N];
void solve() {
  int n;
  scanf("%d", &n);
  unordered_map<ll, int> f;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    f[a[i]]++;
  }
  for(int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  for(int i = 0; i < n; i++) {
    ll x = b[i];
    while(x % 2 != 1) x /= 2;
    while(x > 0) {
      ll y = x;
      bool find = false;
      for(int j = 0; j < 31; j++) {
        if(f.find(y) != f.end() && f[y] > 0) {
          find = true;
          f[y]--;
          break;
        }
        y *= 2;
      }
      if(find) break;
      x /= 2;
    }
  }

  for(auto it = f.begin(); it != f.end(); it++) {
    if(it -> second != 0) {
      printf("NO \n");
      return;
    }
  }
  printf("YES \n");

}

int main() {
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
}
