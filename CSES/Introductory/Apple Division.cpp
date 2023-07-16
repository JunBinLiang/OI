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
 



void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
    }

    ll res = sum;
    for(int i = 0; i < (1 << n); i++) {
        ll x = 0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) x += a[j];
        }
        
        ll y = sum - x;
        res = min(res, abs(x - y));
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
