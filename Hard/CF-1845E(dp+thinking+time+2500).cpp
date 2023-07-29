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
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

//unsigned long long seed = 75;
//unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

const int N = 1510, MOD = 1e9 + 7, M = 61;
int a[N], pos[N], p[N];
int dp[2][M + 2][N], cur[2][M + 2][N]; //[how many off, distance]
int n, k;
void solve() { 
    //freopen("z.txt", "r", stdin);
    //freopen("z.txt", "w", stdout);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
  
    int cnt = 0;
    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i]) {
            cnt++;
            pos[cnt] = i;
            p[i] = 1;
        }
        p[i] += p[i - 1];
    }

    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;

    for(int i = 1; i <= n; i++) {
        memset(cur, 0, sizeof cur);
        if(a[i] == 0) {
            //not take
            for(int off = 0; off <= M; off++) { 
                for(int c = 0; c <= k; c++) {
                    cur[0][off][c] = dp[0][off][c];
                    if(off > 0 && p[i] + off <= cnt) {
                        cur[1][off][c] = dp[1][off][c];
                    }
                }
            }

            //take left
            for(int off = 1; off <= min(M, p[i]); off++) {
                for(int c = 0; c <= k; c++) {
                    int j = pos[p[i] - off + 1];
                    if(c + abs(j - i) <= k) {
                        cur[0][off - 1][c + abs(j - i)] += dp[0][off][c];
                        cur[0][off - 1][c + abs(j - i)] %= MOD;
                    }
                }
            }
            //take right
            for(int off = 1; off <= M && p[i] + off <= cnt; off++) {
                for(int c = 0; c <= k; c++) {
                    int j = pos[p[i] + off];
                    if(c + abs(i - j) <= k) {
                        int add = dp[1][off - 1][c];
                        if(off == 1) add = dp[0][off - 1][c];
                        cur[1][off][c + abs(i - j)] += add;
                        cur[1][off][c + abs(i - j)] %= MOD;
                    }
                }
            }
        } else {
            //not take
            for(int off = 0; off <= M; off++) {
                for(int c = 0; c <= k; c++) {
                    cur[0][off + 1][c] = dp[0][off][c];
                    if(p[i] + off <= cnt) {
                        if(off == 0) {
                            cur[0][off][c] = dp[1][off + 1][c];
                        } else {
                            cur[1][off][c] = dp[1][off + 1][c];
                        }
                    }
                }
            }

            //take left
            for(int off = 0; off <= min(M, p[i] - 1); off++) {
                for(int c = 0; c <= k; c++) {
                    int j = pos[p[i] - off];
                    if(c + abs(i - j) <= k) {
                        cur[0][off][c + abs(i - j)] += dp[0][off][c];
                        cur[0][off][c + abs(i - j)] %= MOD;
                    }
                }
            }

            //taks right
            for(int off = 1; off <= M && off + p[i] - 1 <= cnt; off++) {
                for(int c = 0; c <= k; c++) {
                    int j = pos[p[i] + off];
                    if(c + abs(j - i) <= k) {
                        cur[1][off][c + abs(j - i)] += dp[1][off][c];
                        cur[1][off][c + abs(j - i)] %= MOD;
                    }
                }
            }
        }
        swap(dp, cur);
    }

    ll res = 0;
    for(int i = k % 2; i <= k; i += 2) {
        res += dp[0][0][i];
        res %= MOD;
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

/*
10 10
0 0 1 0 1 1 0 0 1 1
*/

