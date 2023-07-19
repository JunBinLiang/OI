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
 
/*
下凸包最小
向左移动 i -> j + 1
S[i - 1] + a[i] = S[i]
ans[i] = (S[i - 1] - S[j]) - a[i] * i + a[i] * (j + 1) 
ans[i] = (S[i - 1] - S[j]) - a[i] * i + a[i] * j + a[i]

ans[i] = S[i] - S[j] - a[i] * i + a[i] * j
S[j] = a[i] * j - ans[i] + S[i] - a[i] * i => 截距越小，ans[i]越大
(S[j], j) 



下凸包最小反方向
向右移动 i -> j
ans[i] = -(S[j] - S[i]) + a[i] * (j - i)
ans[i] = S[i] - S[j] + a[i] * j - a[i] * i
S[j] = a[i] * j - ans[i] - a[i] * i + S[i] => 截距越小，ans[i]越大
(S[j], j) 
*/

const int N = 2e5 + 10;
ll a[N], p[N];
int q[N];
int n;

ll up(int i, int j) {
    return p[i] - p[j];
}

ll down(int i, int j) {
    return i - j;
}

void solve() {
    cin >> n;

    ll res = 0, sum = 0;
    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        p[i] = a[i] + p[i - 1];
        sum += (a[i] * i);
    }
    res = sum;


    int hh = 0, tt = 1;
    q[0] = 0;
    for(int i = 1; i <= n; i++) {
        int l = hh, r = tt - 2;
        int pos = tt - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(up(q[mid + 1], q[mid]) >= (double)a[i] * down(q[mid + 1], q[mid]) ) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int j = q[pos];
        ll tot = sum - a[i] * i + a[i] * j + p[i] - p[j];
        res = max(res, tot);
        while(tt - hh > 1 && (double)up(q[tt - 1], i) * down(q[tt - 2], q[tt - 1]) <= (double)up(q[tt - 2], q[tt - 1]) * down(q[tt - 1], i)) {
            tt--;
        }
        q[tt++] = i;
    }

    hh = 0; tt = 1;
    q[0] = n;
    for(int i = n - 1; i >= 1; i--) {
        int l = hh, r = tt - 2;
        int pos = tt - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(up(q[mid + 1], q[mid]) >= (double)a[i] * down(q[mid + 1], q[mid]) ) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        int j = q[pos];
        ll tot = sum - (p[j] - p[i]) + a[i] * (j - i);
        res = max(res, tot);
        while(tt - hh > 1 && (double)up(q[tt - 1], i) * down(q[tt - 2], q[tt-1]) >= (double)up(q[tt - 2], q[tt - 1]) * down(q[tt - 1], i)) {
            tt--;
        }
        q[tt++] = i;
        
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
