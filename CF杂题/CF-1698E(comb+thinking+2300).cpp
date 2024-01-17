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
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N  = 2e5 + 10, MOD = 998244353;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n), o(n + 1, -1), p(n + 1, -1);
    FOR(i, 0, n) scanf("%d", &a[i]);
    FOR(i, 0, n) scanf("%d", &b[i]);
    FOR(i, 0, n) {
      o[a[i]] = b[i];
      if(b[i] != -1) {
        p[b[i]] = a[i];
      }
    }
    
    
    
    ll res = 1, count = 0;
    FOR(i, 1, k + 1) {
      if(o[i] == -1) count++;
    }

    FOR(i, 1, n + 1) {
      if(min(i + k, n) < p[i]) { //no answer
        printf("0\n");
        return;
      }
      
      if(i + k <= n && o[i + k] == -1) {
        count++;
      }
      
      if(p[i] == -1) {
          res *= count;
          res %= MOD;
          count--;
      }
    }

    printf("%lld\n", res);
}
    

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
