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
Take from j + 1 to i
ans[i] = SS[i] - SS[j] - (S[i] - S[j]) * (j)
ans[i] = SS[i] - SS[j] - S[i] * j + S[j] * j

S[j] * j - SS[j] = S[i] * j + ans[i] - SS[i]
(S[j] * j - SS[j], j)
*/

const int N = 2e5 + 10;
int a[N], q[N], n;
ll S[N], SS[N], res = 0;

ll up(int i, int j) {
    return (S[i] * i - SS[i]) - (S[j] * j - SS[j]);
}

ll down(int i, int j) {
    return i - j;
}

void solve() {
    S[0] = SS[0] = 0;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        S[i] = S[i - 1] + a[i];
        SS[i] = (a[i] + 0ll) * i;
        SS[i] += SS[i - 1];
    }
    
    int hh = 0, tt = 1;
    q[0] = 0;

    for(int i = 1; i <= n; i++) {
        int l = 0, r = tt - 2;
        int pos = tt - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(up(q[mid + 1], q[mid]) <= down(q[mid + 1], q[mid]) * S[i]) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        int j = q[pos];
        ll v = SS[i] - SS[j] - (S[i] - S[j]) * j;
        res = max(res, v);

        while(tt - hh > 1 && up(q[tt - 1], i) * down(q[tt - 2], q[tt - 1]) >= up(q[tt - 2], q[tt - 1]) * down(q[tt - 1], i)) {
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
