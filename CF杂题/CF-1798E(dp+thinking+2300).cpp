
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 3e5 + 10;
int a[N], ans[N], dp[N], f[N];
int n;
void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        ans[i] = 2;
        dp[i] = -1;
        f[i] = 1;
    }

    //ans : 0, 1, 2
    set<int> s;
    for(int i = n - 2; i >= 0; i--) {
        int v = a[i];
        if(i + v < n) {
            if(i + v == n - 1) dp[i] = 1;
            else {
                if(dp[i + v + 1] != -1) {
                    dp[i] = 1 + dp[i + v + 1];
                } else {
                    dp[i] = -1;
                }
            }
        } else {
            dp[i] = -1;
        }

        //cout << i << "  " << s << endl;

        if(s.size() > 0) {
            auto best = s.end();
            best--;
            f[i] = (*best) + 1;
        }

        if(i + 1 + v < n && f[i + 1 + v] != -1) {
            f[i] = max(f[i], 1 + f[i + 1 + v]);
        }
        


        if(dp[i + 1] != -1) {
            if(v == dp[i + 1]) ans[i] = 0;
            else ans[i]  = 1;
        } else {
            if(v == 1) {
                ans[i] = 1;
            } else {
                if (f[i + 1] >= v) {
                    ans[i] = 1;
                }
                
            }
        }
        if(dp[i] != -1) {
            s.insert(dp[i]);
        }
    }

    for(int i = 0; i < n - 1; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main()
{   
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
