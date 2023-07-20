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
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 

ll LCM(int x, int y) {
    return (x + 0ll) * y / __gcd(x, y);
}

const int N = 3e5 + 10;
ll INF = N * 40;
int a[N], nxt[N];
int n;
void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    set<int> s, sub;
    for(int i = 0; i < n; i++) {
        int x = a[i];
        s.insert(x);
        set<int> cur;

        for(auto y : sub) {
            ll lcm = LCM(x, y);
            if(lcm <= INF) {
                cur.insert((int)(lcm));
                s.insert((int)(lcm));
            } 
        }
        cur.insert(x);
        sub = cur;
    }
    


    ll res = 1;
    while(s.find(res) != s.end()) {
        res++;
    }
    cout << res << endl;
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
