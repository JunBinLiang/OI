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
 


const int N = 2010, INF = 1e9;
int dp[N][N], n;
void solve() {
    cin >> n;
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x = abs(x);
        a.push_back({x, i});
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            dp[i][j] = INF;
        }
    }

    int res = 0;
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        int j = i, cnt = 0;
        
        while(j < n && a[i].first == a[j].first) {
            cnt++;
            int p = a[j].second;
            int w1 = 0, w2 = 0; // neg cost, pos cost
            for(int x = 0; x < i; x++) {
                if(a[x].second < p) {
                    w1++;
                } else {
                    w2++;
                }
            }
            
            if(j == i) {
                dp[j][0] = w2; //no negative
                dp[j][1] = w1; //one negative
            } else {
                for(int x = 0; x <= cnt ; x++) {
                    dp[j][x] = dp[j - 1][x] + w2;
                    if(x - 1 >= 0) {
                        int add = 0;
                        if(a[i].first != 0) add = (cnt - 1 - (x - 1));
                        dp[j][x] = min(dp[j][x], w1 + dp[j - 1][x - 1] + add);
                    }
                }
            }
            j++;
        }
        
        

        int mn = 1e9;
        for(int x = 0; x <= cnt; x++) {
            mn = min(mn, dp[j - 1][x]);
        }
        res += mn;
        i = j - 1;
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
