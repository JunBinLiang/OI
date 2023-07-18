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
 


//time to take a[j + 1 : i] => a[i] * (i - j) - SUM(a[j + 1 : i]) 
//dp[i] = dp[j] + a[i] * (i - j) - S[i] + S[j]

//dp[j] is from last person
//dp[i] = dp[j] + a[i] * i - a[i] * j - S[i] + S[j]


//dp[j] + S[j] = dp[i] - a[i] * i + a[i] * j + S[i]
//dp[j] + S[j] = (a[i] * j) + (dp[i] - a[i] * i + S[i])

//a[i] * j 单调递增

//(dp[j] + S[j], j)

const int N = 1e5 + 10;
int D[N], q[N];
ll S[N];
ll dp[105][N];

ll up(int i, int x1, int x2) {
    return (dp[i][x1] + S[x1]) - (dp[i][x2] + S[x2]);
}
ll down(int x1, int x2) {
    return x1 - x2;
}

//下凸包求最小
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    
    D[0] = D[1] = 0; //distance
    for(int i = 2; i <= n; i++) {
        cin >> D[i];
        D[i] += D[i - 1]; 
    }

    vector<ll> a(m + 1, 0); //time for cat
    for(int i = 1; i <= m; i++) {
        int h, t;
        cin >> h >> t;
        a[i] = t - D[h];
    }

    sort(a.begin() + 1, a.end());
    S[0] = 0;
    for(int i = 1; i <= m; i++) {
        S[i] = S[i - 1] + a[i];
    }

    memset(dp, 0, sizeof dp);
    for(int i = 1; i < a.size(); i++) {
        dp[1][i] = (a[i] * i) - (S[i] - S[0]); //time to take the first i cats
    }

    for(int x = 2; x <= p; x++) {
        int hh = 0, tt = 1;
        q[0] = 0;
        
        for(int i = 1; i <= m; i++) {
            while(tt - hh > 1 && up(x - 1, q[hh + 1], q[hh]) <= a[i] * down(q[hh + 1], q[hh])) {
                hh++;
            } 

            int j = q[hh];
            dp[x][i] = dp[x - 1][j] + a[i] * (i - j) - (S[i] - S[j]);  
            
            while(tt - hh > 1 && 
            up(x - 1, i, q[tt - 1]) * down(q[tt - 1], q[tt - 2]) <= up(x - 1, q[tt - 1], q[tt - 2])* down(i, q[tt - 1])) {
                tt--;
            }
            q[tt++] = i;
        }
    }

    cout << dp[p][m] << endl;
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
